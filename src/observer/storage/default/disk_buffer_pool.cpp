// __CR__
// Copyright (c) 2021 LongdaFeng All Rights Reserved
//
// This software contains the intellectual property of LongdaFeng
// or is licensed to LongdaFeng from third parties.  Use of this
// software and the intellectual property contained therein is
// expressly limited to the terms and conditions of the License Agreement
// under which it is provided by or on behalf of LongdaFeng.
// __CR__
//
// Created by Longda on 2021/4/13.
//
#include "disk_buffer_pool.h"
#include <errno.h>
#include <string.h>

#include "common/log/log.h"

using namespace common;


DiskBufferPool* theGlobalDiskBufferPool() {
  static DiskBufferPool *instance = new DiskBufferPool();

  return instance;
}

const RC DiskBufferPool::createFile(const char *fileName) {
  int fd = open(fileName, O_RDWR | O_CREAT | O_EXCL ,
                 S_IREAD | S_IWRITE);
  if (fd < 0) {
    LOG_ERROR("Failed to create %s, due to %s.", fileName, strerror(errno));
    return RC::SCHEMA_DB_EXIST;
  }

  close(fd);

  /**
   * Here don't care about the failure
   */
  fd = open(fileName, O_RDWR);

  Page page;
  memset(&page, 0, sizeof(Page));

  BPFileSubHeader *fileSubHeader;
  fileSubHeader = (BPFileSubHeader *)page.data;
  fileSubHeader->allocatedPages = 1;
  fileSubHeader->pageCount = 1;

  char *bitmap = page.data + (int)BP_FILE_SUB_HDR_SIZE;
  bitmap[0] |= 0x01;
  if (lseek(fd, 0, SEEK_SET) == -1) {
    LOG_ERROR("Failed to seek file %s to position 0, due to %s .", fileName,
              strerror(errno));
    return RC::IOERR_SEEK;
  }

  if (write(fd, (char *)&page, sizeof(Page)) != sizeof(Page)) {
    LOG_ERROR("Failed to write header to file %s, due to %s.", fileName,
              strerror(errno));
    close(fd);
    return RC::IOERR_WRITE;
  }

  close(fd);
  LOG_INFO("Successfully create %s.", fileName);
  return RC::SUCCESS;
}

const RC DiskBufferPool::openFile(char *fileName, int *fileID) {
  int fd, i;
  // TODO,  This part isn't gentle, the better method is using LRU queue.
  for (i = 0; i < MAX_OPEN_FILE; i++) {
    if (openList[i]) {
      if (!strcmp(openList[i]->fileName, fileName))
        LOG_INFO("%s has already been opened.", fileName);
      return RC::SUCCESS;
    }
  }
  i = 0;
  while (i < MAX_OPEN_FILE && openList[i++])
    ;
  if (i >= MAX_OPEN_FILE && openList[i - 1]) {
    LOG_ERROR("Failed to open file %s, because too much files has been opened.",
              fileName);
    return RC::BUFFERPOOL_OPEN_TOO_MANY_FILES;
  }

  if ((fd = open(fileName, O_RDWR)) < 0) {
    LOG_ERROR("Failed to open file %s, because %s.", fileName, strerror(errno));
    return RC::IOERR_ACCESS;
  }
  LOG_INFO("Successfully open file %s.", fileName);

  BPFileHandle *fileHandle = new BPFileHandle();
  if (fileHandle == NULL) {
    LOG_ERROR("Failed to alloc memory of BPFileHandle for %s.", fileName);
    close(fd);
    return RC::NOMEM;
  }

  RC tmp;
  fileHandle->bopen = true;
  // TODO
  // The filename's memory is likely to exist problem
  fileHandle->fileName = fileName;
  fileHandle->fileDesc = fd;
  if ((tmp = allocateBlock(&fileHandle->pHdrFrame)) != RC::SUCCESS) {
    LOG_ERROR("Failed to allocate block for %s's BPFileHandle.", fileName);
    delete fileHandle;
    close(fd);
    return tmp;
  }
  fileHandle->pHdrFrame->dirty = false;
  fileHandle->pHdrFrame->accTime = clock();
  fileHandle->pHdrFrame->fileDesc = fd;
  fileHandle->pHdrFrame->pinCount = 1;
  if ((tmp = loadPage(0, fileHandle, fileHandle->pHdrFrame)) != RC::SUCCESS) {
    fileHandle->pHdrFrame->pinCount = 0;
    disposeBlock(fileHandle->pHdrFrame);
    close(fd);
    delete fileHandle;
    return tmp;
  }

  fileHandle->pHdrPage = &(fileHandle->pHdrFrame->page);
  fileHandle->pBitmap = fileHandle->pHdrPage->data + BP_FILE_SUB_HDR_SIZE;
  fileHandle->pFileSubHeader = (BPFileSubHeader *)fileHandle->pHdrPage->data;
  openList[i - 1] = fileHandle;
  *fileID = i - 1;
  LOG_INFO("Successfully open %s.", fileName);
  return RC::SUCCESS;
}

const RC DiskBufferPool::closeFile(int fileID) {
  RC tmp;
  if ((tmp = checkFileId(fileID)) != RC::SUCCESS) {
    LOG_ERROR("Failed to close file, due to invalid fileId %d", fileID);
    return tmp;
  }

  BPFileHandle *fileHandle = openList[fileID];
  fileHandle->pHdrFrame->pinCount--;
  if ((tmp = forceAllPages(fileHandle)) != RC::SUCCESS) {
    LOG_ERROR("Failed to closeFile %d:%s, due to failed to force all pages.",
              fileID, fileHandle->fileName);
    return tmp;
  }

  if (close(fileHandle->fileDesc) < 0) {
    LOG_ERROR("Failed to close fileId:%d, fileName:%s, error:%s", fileID,
              fileHandle->fileName, strerror(errno));
    return RC::IOERR_CLOSE;
  }
  openList[fileID] = NULL;
  delete (fileHandle);
  return RC::SUCCESS;
}

const RC DiskBufferPool::getThisPage(int fileID, PageNum pageNum, BPPageHandle *pageHandle) {
  RC tmp;
  if ((tmp = checkFileId(fileID)) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %d, due to invalid fileId %d", pageNum,
              fileID);
    return tmp;
  }

  BPFileHandle *fileHandle = openList[fileID];
  if ((tmp = checkPageNum(pageNum, fileHandle)) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d, due to invalid pageNum.",
              fileHandle->fileName, pageNum);
    return tmp;
  }

  BPPageHandle *pPageHandle = pageHandle;
  pPageHandle->open = true;
  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (bpManager.allocated[i] == false)
      continue;
    if (bpManager.frame[i].fileDesc != fileHandle->fileDesc)
      continue;

    // This page has been loaded.
    if (bpManager.frame[i].page.pageNum == pageNum) {
      pPageHandle->pFrame = bpManager.frame + i;
      pPageHandle->pFrame->pinCount++;
      pPageHandle->pFrame->accTime = clock();
      return RC::SUCCESS;
    }
  }

  // Allocate one page and load the data into this page
  if ((tmp = allocateBlock(&(pPageHandle->pFrame))) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d, due to failed to alloc page.",
              fileHandle->fileName, pageNum);
    return tmp;
  }
  pPageHandle->pFrame->dirty = false;
  pPageHandle->pFrame->fileDesc = fileHandle->fileDesc;
  pPageHandle->pFrame->pinCount = 1;
  pPageHandle->pFrame->accTime = clock();
  if ((tmp = loadPage(pageNum, fileHandle, pPageHandle->pFrame)) !=
      RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d", fileHandle->fileName);
    pPageHandle->pFrame->pinCount = 0;
    disposeBlock(pPageHandle->pFrame);
    return tmp;
  }

  return RC::SUCCESS;
}

const RC DiskBufferPool::allocatePage(int fileID, BPPageHandle *pageHandle) {
  RC tmp;
  if ((tmp = checkFileId(fileID)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page, due to invalid fileId %d", fileID);
    return tmp;
  }

  BPFileHandle *fileHandle = openList[fileID];
  BPPageHandle *pPageHandle = pageHandle;

  int byte = 0, bit = 0;
  if ((fileHandle->pFileSubHeader->allocatedPages) <
      (fileHandle->pFileSubHeader->pageCount)) {
    // There is one free page
    for (int i = 0; i < fileHandle->pFileSubHeader->pageCount; i++) {
      byte = i / 8;
      bit = i % 8;
      if (((fileHandle->pBitmap[byte]) & (1 << bit)) == 0) {
        (fileHandle->pFileSubHeader->allocatedPages)++;
        fileHandle->pBitmap[byte] |= (1 << bit);
        return getThisPage(fileID, i, pageHandle);
      }
    }

  }

  if ((tmp = allocateBlock(&(pPageHandle->pFrame))) != RC::SUCCESS) {
    LOG_ERROR("Failed to allocate page %s, due to no free page.",
              fileHandle->fileName);
    return tmp;
  }


  fileHandle->pFileSubHeader->allocatedPages++;
  fileHandle->pFileSubHeader->pageCount++;
  byte = fileHandle->pFileSubHeader->pageCount / 8;
  bit = fileHandle->pFileSubHeader->pageCount % 8;
  fileHandle->pBitmap[byte] |= (1 << bit);
  fileHandle->pHdrFrame->dirty = true;

  pPageHandle->pFrame->dirty = false;
  pPageHandle->pFrame->fileDesc = fileHandle->fileDesc;
  pPageHandle->pFrame->pinCount = 1;
  pPageHandle->pFrame->accTime = clock();
  memset(&(pPageHandle->pFrame->page), 0, sizeof(Page));
  pPageHandle->pFrame->page.pageNum = fileHandle->pFileSubHeader->pageCount - 1;

  // Use flush operation to extion file
  if ((tmp = flushBlock(pPageHandle->pFrame)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page %s , due to failed to extend one page.",
              fileHandle->fileName);
    return tmp;
  }

  return RC::SUCCESS;
}

const RC DiskBufferPool::getPageNum(BPPageHandle *pageHandle, PageNum *pageNum) {
  if (pageHandle->open == false)
    return RC::BUFFERPOOL_CLOSED;
  *pageNum = pageHandle->pFrame->page.pageNum;
  return RC::SUCCESS;
}

const RC DiskBufferPool::getData(BPPageHandle *pageHandle, char **data) {
  if (pageHandle->open == false)
    return RC::BUFFERPOOL_CLOSED;
  *data = pageHandle->pFrame->page.data;
  return RC::SUCCESS;
}

const RC DiskBufferPool::markDirty(BPPageHandle *pageHandle) {
  pageHandle->pFrame->dirty = true;
  return RC::SUCCESS;
}

const RC DiskBufferPool::unpinPage(BPPageHandle *pageHandle) {
  pageHandle->pFrame->pinCount--;
  return RC::SUCCESS;
}

/**
 * disposePage will delete the data of the page of pageNum
 * forcePage will flush the page of pageNum
 * @param fileID
 * @param pageNum
 * @return
 */
const RC DiskBufferPool::disposePage(int fileID, PageNum pageNum) {
  RC rc;
  if ((rc = checkFileId(fileID)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page, due to invalid fileId %d", fileID);
    return rc;
  }

  BPFileHandle *fileHandle = openList[fileID];
  if ((rc = checkPageNum(pageNum, fileHandle)) != RC::SUCCESS) {
    LOG_ERROR("Failed to dispose page %s:%d, due to invalid pageNum",
              fileHandle->fileName, pageNum);
    return rc;
  }

  fileHandle->pHdrFrame->dirty = true;
  fileHandle->pFileSubHeader->allocatedPages--;
  char tmp = 1 << (pageNum % 8);
  fileHandle->pBitmap[pageNum / 8] &= ~tmp;
  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (bpManager.allocated[i] == false)
      continue;
    if (bpManager.frame[i].fileDesc != fileHandle->fileDesc) {
      continue;
    }

    if (bpManager.frame[i].page.pageNum == pageNum) {
      if (bpManager.frame[i].pinCount != 0)
        return RC::BUFFERPOOL_PAGEPINNED;
      bpManager.allocated[i] = false;
      return RC::SUCCESS;
    }
  }
  return RC::SUCCESS;
}

/**
 * disposePage will delete the data of the page of pageNum
 * forcePage will flush the page of pageNum
 * @param fileHandle
 * @param pageNum
 * @return
 */
const RC DiskBufferPool::forcePage(BPFileHandle *fileHandle, PageNum pageNum) {
  int i;
  for (i = 0; i < BP_BUFFER_SIZE; i++) {
    if (bpManager.allocated[i] == false)
      continue;

    Frame *frame = &bpManager.frame[i];
    if (frame->fileDesc != fileHandle->fileDesc)
      continue;
    if (frame->page.pageNum != pageNum) {
      continue;
    }

    if (frame->pinCount != 0) {
      LOG_ERROR("Page :%s:%d has been pinned.", fileHandle->fileName, pageNum);
      return RC::BUFFERPOOL_PAGEPINNED;
    }

    if (frame->dirty == true) {
      RC rc = RC::SUCCESS;
      if ((rc = flushBlock(frame)) != RC::SUCCESS) {
        LOG_ERROR("Failed to flush page:%s:%d.", fileHandle->fileName, pageNum);
        return rc;
      }
    }
    bpManager.allocated[i] = false;
    return RC::SUCCESS;
  }
  return RC::SUCCESS;
}

const RC DiskBufferPool::forceAllPages(BPFileHandle *fileHandle) {

  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (bpManager.allocated[i] == false)
      continue;
    if (bpManager.frame[i].fileDesc != fileHandle->fileDesc)
      continue;

    if (bpManager.frame[i].dirty == true) {
      RC rc = flushBlock(&bpManager.frame[i]);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to flush all pages' of %s.", fileHandle->fileName);
        return rc;
      }
    }
    bpManager.allocated[i] = false;
  }
  return RC::SUCCESS;
}

const RC DiskBufferPool::flushBlock(Frame *frame) {
  // TODO
  // The better way is use mmap the block into memory,
  // so it is easier to flush data to file.

  s64_t offset = ((s64_t)frame->page.pageNum) * sizeof(Page);
  if (lseek(frame->fileDesc, offset, SEEK_SET) == offset - 1) {
    LOG_ERROR("Failed to flush page %lld of %d due to failed to seek %s.",
              offset, frame->fileDesc, strerror(errno));
    return RC::IOERR_SEEK;
  }

  if (write(frame->fileDesc, &(frame->page), sizeof(Page)) != sizeof(Page)) {
    LOG_ERROR("Failed to flush page %lld of %d due to %s.", offset,
              frame->fileDesc, strerror(errno));
    return RC::IOERR_WRITE;
  }
  frame->dirty = false;

  return RC::SUCCESS;
}

const RC DiskBufferPool::allocateBlock(Frame **buffer) {

  // There is one Frame which is free.
  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (bpManager.allocated[i] == false) {
      bpManager.allocated[i] = true;
      *buffer = bpManager.frame + i;
      return RC::SUCCESS;
    }
  }

  int min = 0;
  clock_t mintime = 0;
  bool flag = false;
  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (bpManager.frame[i].pinCount != 0)
      continue;
    if (flag == false) {
      flag = true;
      min = i;
      mintime = bpManager.frame[i].accTime;
    }
    if (bpManager.frame[i].accTime < mintime) {
      min = i;
      mintime = bpManager.frame[i].accTime;
    }
  }
  if (flag == false) {
    LOG_ERROR("All pages have been used and pinned.");
    return RC::NOMEM;
  }

  if (bpManager.frame[min].dirty == true) {
    RC rc = flushBlock(&(bpManager.frame[min]));
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  *buffer = bpManager.frame + min;
  return RC::SUCCESS;
}

const RC DiskBufferPool::disposeBlock(Frame *buf) {
  if (buf->pinCount != 0) {
    LOG_WARN("Begin to free page %d of %d, but it's pinned.", buf->page.pageNum,
             buf->fileDesc);
    return RC::LOCKED_UNLOCK;
  }
  if (buf->dirty == true) {
    RC rc = flushBlock(buf);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  buf->dirty = false;
  int pos = buf - bpManager.frame;
  bpManager.allocated[pos] = false;
  return RC::SUCCESS;
}

const RC DiskBufferPool::checkFileId(int fileID) {
  if (fileID < 0 || fileID >= MAX_OPEN_FILE) {
    LOG_ERROR("Invalid fileId:%d.", fileID);
    return RC::BUFFERPOOL_ILLEGAL_FILE_ID;
  }
  if (!openList[fileID]) {
    LOG_ERROR("Invalid fileId:%d, it is empty.", fileID);
    return RC::BUFFERPOOL_ILLEGAL_FILE_ID;
  }
}

const RC DiskBufferPool::getPageCount(int fileID, int *pageCount) {
  RC rc = RC::SUCCESS;
  if ((rc = checkFileId(fileID)) != RC::SUCCESS) {
    return rc;
  }
  *pageCount = openList[fileID]->pFileSubHeader->pageCount;
  return RC::SUCCESS;
}

const RC DiskBufferPool::checkPageNum(PageNum pageNum, BPFileHandle *fileHandle) {
  if (pageNum >= fileHandle->pFileSubHeader->pageCount) {
    LOG_ERROR("Invalid pageNum:%d, file's name:%s", pageNum,
              fileHandle->fileName);
    return RC::BUFFERPOOL_INVALIDPAGENUM;
  }
  if ((fileHandle->pBitmap[pageNum / 8] & (1 << (pageNum % 8))) == 0) {
    LOG_ERROR("Invalid pageNum:%d, file's name:%s", pageNum,
              fileHandle->fileName);
    return RC::BUFFERPOOL_INVALIDPAGENUM;
  }
  return RC::SUCCESS;
}

const RC DiskBufferPool::loadPage(int pageNum, BPFileHandle *fileHandle, Frame *frame) {
  s64_t offset = ((s64_t)pageNum) * sizeof(Page);
  if (lseek(fileHandle->fileDesc, offset, SEEK_SET) == offset - 1) {
    LOG_ERROR("Failed to load page %s:%d, due to failed to lseek:%s.",
              fileHandle->fileName, pageNum, strerror(errno));

    return RC::IOERR_SEEK;
  }
  if (read(fileHandle->fileDesc, &(frame->page), sizeof(Page)) !=
      sizeof(Page)) {
    LOG_ERROR("Failed to load page %s:%d, due to failed to read data:%s.",
              fileHandle->fileName, pageNum, strerror(errno));
    return RC::IOERR_READ;
  }
  return RC::SUCCESS;
}
