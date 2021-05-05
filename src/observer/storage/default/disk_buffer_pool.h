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
#ifndef __OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_
#define __OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

#include <string.h>
#include <sys/stat.h>
#include <time.h>


#include "rc.h"

typedef unsigned int PageNum;

//
#define BP_PAGE_SIZE (1 << 12)
#define BP_PAGE_DATA_SIZE (BP_PAGE_SIZE - sizeof(PageNum))
#define BP_FILE_SUB_HDR_SIZE (sizeof(BPFileSubHeader))
#define BP_BUFFER_SIZE 50
#define MAX_OPEN_FILE 50



typedef struct {
  PageNum pageNum;
  char data[BP_PAGE_DATA_SIZE];
} Page;
// sizeof(Page) should be equal to BP_PAGE_SIZE

typedef struct {
  PageNum pageCount;
  int allocatedPages;
} BPFileSubHeader;

typedef struct {
  bool dirty;
  unsigned int pinCount;
  clock_t accTime;
  int fileDesc;
  Page page;
} Frame;

typedef struct {
  bool open;
  Frame *pFrame;
} BPPageHandle;

class BPFileHandle{
public:
  BPFileHandle() {
    memset(this, 0, sizeof(*this));
  }

public:
  bool bopen;
  char *fileName;
  int fileDesc;
  Frame *pHdrFrame;
  Page *pHdrPage;
  char *pBitmap;
  BPFileSubHeader *pFileSubHeader;


} ;

/**
 * TODO
 * 当前BPManager 太简单， 直接使用全局变量， 把所有的Frame 直接拥有，
 * 当内存量非常大的时候， 这个地方很容易出问题。
 *
 * 更好的做法是， 使用内存池算法， 动态申请
 *
 * 这里可以做为一个考题：
 */
class BPManager {
public:
  BPManager() {
    for (int i = 0; i < BP_BUFFER_SIZE; i++) {
      allocated[i] = false;
      frame[i].pinCount = 0;
    }
  }

  void setReads(int reads) { this->reads = reads; }

  int getReads() { return reads; }

  void setWrites(int writes) { this->writes = writes; }

  int getWrites() { return writes; }

  Frame *getFrame() { return frame; }

  bool *getAllocated() { return allocated; }

public:
  int reads;
  int writes;
  Frame frame[BP_BUFFER_SIZE];
  bool allocated[BP_BUFFER_SIZE];
};

class DiskBufferPool {
public:
  /**
  * 创建一个名称为指定文件名的分页文件
  * @param fileName
  * @return
  */
  const RC createFile(const char *fileName);

/**
 * 根据文件名打开一个分页文件，返回文件ID
 * @param fileName
 * @param fileID
 * @return
 */
  const RC openFile(char *fileName, int *fileID);

/**
 * 关闭fileID对应的分页文件
 * @param fileID
 * @return
 */
  const RC closeFile(int fileID);

/**
 * 根据文件ID和页号获取指定页面到缓冲区，返回页面句柄指针。
 * @param fileID
 * @param pageNum
 * @param pageHandle
 * @return
 */
  const RC getThisPage(int fileID, PageNum pageNum, BPPageHandle *pageHandle);

/**
 * 在指定文件中分配一个新的页面，并将其放入缓冲区，返回页面句柄指针。
 * 分配页面时，如果文件中有空闲页，就直接分配一个空闲页；
 * 如果文件中没有空闲页，则扩展文件规模来增加新的空闲页。
 * @param fileID
 * @param pageHandle
 * @return
 */
  const RC allocatePage(int fileID, BPPageHandle *pageHandle);

/**
 * 根据页面句柄指针返回对应的页面号
 * @param pageHandle
 * @param pageNum
 * @return
 */
  const RC getPageNum(BPPageHandle *pageHandle, PageNum *pageNum);

/**
 * 根据页面句柄指针返回对应的数据区指针
 * @param pageHandle
 * @param data
 * @return
 */
  const RC getData(BPPageHandle *pageHandle, char **data);

/**
 * 丢弃文件中编号为pageNum的页面，将其变为空闲页
 * @param fileID
 * @param pageNum
 * @return
 */
  const RC disposePage(int fileID, PageNum pageNum);

/**
 * 标记指定页面为“脏”页。如果修改了页面的内容，则应调用此函数，
 * 以便该页面被淘汰出缓冲区时系统将新的页面数据写入磁盘文件
 * @param pageHandle
 * @return
 */
  const RC markDirty(BPPageHandle *pageHandle);

/**
 * 此函数用于解除pageHandle对应页面的驻留缓冲区限制。
 * 在调用GetThisPage或AllocatePage函数将一个页面读入缓冲区后，
 * 该页面被设置为驻留缓冲区状态，以防止其在处理过程中被置换出去，
 * 因此在该页面使用完之后应调用此函数解除该限制，使得该页面此后可以正常地被淘汰出缓冲区
 * @param pageHandle
 * @return
 */
  const RC unpinPage(BPPageHandle *pageHandle);

/**
 * 获取文件的总页数
 * @param fileID
 * @param pageCount
 * @return
 */
  const RC getPageCount(int fileID, int *pageCount);



protected:
  const RC allocateBlock(Frame **buf);
  const RC disposeBlock(Frame *buf);
  const RC forcePage(BPFileHandle *fileHandle, PageNum pageNum);
  const RC forceAllPages(BPFileHandle *fileHandle);
  const RC checkFileId(int fileID);
  const RC checkPageNum(PageNum pageNum, BPFileHandle *fileHandle);
  const RC loadPage(int pageNum, BPFileHandle *fileHandle, Frame *frame);
  const RC flushBlock(Frame *frame);

private:
  BPManager bpManager;
  BPFileHandle *openList[MAX_OPEN_FILE];

};

DiskBufferPool *theGlobalDiskBufferPool();

#endif //__OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_
