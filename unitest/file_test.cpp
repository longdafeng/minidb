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
// Created by Longda on 2021
//

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "file_test.h"

FileTest::FileTest() {
  // TODO Auto-generated constructor stub
}

FileTest::~FileTest() {
  // TODO Auto-generated destructor stub
}

int FileTest::openfile() {
  const char *fileName = "mytest";
  int flags = O_RDWR | O_CREAT;
  int fd = open(fileName, flags, S_IRWXU | S_IRWXG | S_IRWXO);
  if (fd == -1) {
    std::cerr << "Failed to open " << fileName;
    return -1;
  }

  const int BUF_LEN = 1024;
  char writeBuf[BUF_LEN] = "Write data";
  ssize_t count = write(fd, writeBuf, BUF_LEN);
  if (count == -1) {
    std::cerr << "Failed to open " << fileName;
    close(fd);
    return -1;
  }

  off_t pos = lseek(fd, 0, SEEK_SET);
  if (pos == -1) {
    std::cerr << "Failed to lseek " << fileName;
    close(fd);
    return -1;
  }

  char readBuf[BUF_LEN] = {0};

  ssize_t readCount = read(fd, readBuf, BUF_LEN);
  if (readCount == -1) {
    std::cerr << "Failed to read " << fileName;
    close(fd);
    return -1;
  }

  std::cout << readBuf << std::endl;

  return 0;
}

void FileTest::open_lseek() {
  int fd = open("open_file", O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IROTH);
  // int flags = O_WRONLY;
  // int fd = open("create_file", flags);
  if (fd < 0) {
    std::cerr << "Failed to open file " << errno << "," << strerror(errno)
              << std::endl;
    return;
  }

  if (lseek(fd, 024, SEEK_SET) < 0) {
    close(fd);
    std::cerr << "Failed to lseek " << errno << "," << strerror(errno)
              << std::endl;
    return;
  }

  char buffer[] = "write data";
  int bufLen = sizeof(buffer);
  if (write(fd, buffer, bufLen) < bufLen) {
    close(fd);
    std::cerr << "Failed to write " << errno << "," << strerror(errno)
              << std::endl;
    return;
  }

  close(fd);
  return;
}

int FileTest::fstream() {
  const int BUF_LEN = 1024;
  char readBuf[BUF_LEN] = "Write data";
  std::fstream fs;
  fs.open("./LoadFastDFS.trace.enterprise.7.msg", (std::ios_base::openmode)25);
  if (!fs) {
    std::cerr << "Failed to open" << std::endl;
    return -1;
  }
  while (fs.eof() == false) {
    fs.getline(readBuf, sizeof(readBuf));
    if (!fs) {
      std::cerr << "!fs error" << std::endl;
    }
    if (fs.good() == false) {
      std::cerr << "fs.good() error" << std::endl;
    }
    std::cout << readBuf << std::endl;
  }
  return 0;
}

int FileTest::readdir(int argc, char **argv) {
  DIR *dir;
  struct dirent *ptr;
  int i = 0;
  if (argc == 1)
    dir = opendir("./");
  else
    dir = opendir(argv[1]);
  while ((ptr = ::readdir(dir)) != NULL) {
    printf("d_name: %s\n", ptr->d_name); //需要更详细的信息你可以修改该句
    i++;
  }
  closedir(dir);

  return 0;
}

int FileTest::ifstream() {
  char buf[4096];
  memset(buf, 1, 4096);
  std::ifstream iff("/rubish");
  if (!iff) {
    std::cout << "failed to read" << std::endl;
    return -1;
  }

  if (!iff.good()) {
    std::cout << "fail to create" << std::endl;
    return -1;
  }
  iff.getline(buf, 4096);

  std::cout << buf << ":" << strlen(buf) << std::endl;
  std::cout << "finish" << std::endl;
  iff.close();
  return 0;
}

int FileTest::ofstream() {
  std::ofstream ofs("ofs_stream_test");

  if (!ofs) {
    std::cerr << "failed to construct ofs " << strerror(errno) << ":" << errno
              << std::endl;
    return errno;
  }

  if (!ofs.seekp(2024, std::ios_base::beg)) {
    ofs.close();

    std::cerr << "Failed to seek " << strerror(errno) << ":" << errno
              << std::endl;
    return errno;
  }

  const char writeBuf[] = "buffers_write data";
  if (!ofs.write(writeBuf, sizeof(writeBuf))) {
    ofs.close();
    std::cerr << "Failed to write " << strerror(errno) << ":" << errno
              << std::endl;
    return errno;
  }

  std::cout << "Successfully write data" << std::endl;
  ofs.close();
  return 0;
}

void FileTest::ofstream_loop() {
  int i = 0;
  while (1) {
    if (ofstream()) {
      break;
    }
    i++;
    if (i % 1000 == 0) {
      std::cout << "open " << i << " times" << std::endl;
    }
  }
  return;
}

void FileTest::binlog() {
  typedef struct _binlog {
    char name[256];
    int node;
    int mode;
  } BinLog;

  FILE *fd = ::fopen("test.file.op", "r+");
  if (fd == NULL) {
    std::cerr << "Failed to open log.cpp" << std::endl;
    return;
  }

  for (int i = 0; i < 20; i++) {
    BinLog binLog;
    sprintf(binLog.name, "name:%d", i);
    binLog.node = i;
    binLog.mode = i << 8;

    char line[1024] = {0};
    memcpy(line, &binLog, sizeof(binLog));
    line[sizeof(binLog)] = '\n';

    int writeNum = fwrite(line, 1, sizeof(binLog) + 1, fd);
    if (writeNum < int(sizeof(binLog) + 1)) {
      std::cerr << "Write nothing:" << errno << ":" << strerror(errno)
                << std::endl;
      break;
    }
  }

  rewind(fd);

  while (1) {
    char line[1024];
    char *data = fgets(line, sizeof(line), fd);
    if (data == NULL) {
      std::cout << "read finish" << std::endl;
      break;
    }
    BinLog *binLog = (BinLog *)line;

    std::cout << "name:" << binLog->name << "node:" << binLog->node
              << "mode:" << binLog->mode << std::endl;
  }

  fclose(fd);
  return;
}

void FileTest::fopen() {
  const char *fileName = "fseekwrite";
  FILE *fd = ::fopen(fileName, "r+");
  if (fd == NULL) {
    std::cout << "failed to open " << fileName << std::endl;
    return;
  }

  fseek(fd, 1024, SEEK_SET);

  char buffer[1024] = "buffer";
  if (fwrite(buffer, 1, strlen(buffer), fd) == 0) {
    std::cout << "failed to write" << fileName << " error " << strerror(errno)
              << std::endl;
  }
  fflush(fd);
  fclose(fd);
}

int main(int argc, char **argv) { return 0; }