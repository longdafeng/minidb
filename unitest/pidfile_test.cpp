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
// Created by Longda on 2021/4/16.
//
#include <unistd.h>

#include "gtest/gtest.h"

#include "common/os/pidfile.h"
#include "common/io/io.h"
#include "common/lang/string.h"

using namespace common;

int main() {
  long long pid = (long long)getpid();

  const char *programName = "test";
  writePidFile(programName);

  std::string pidFile = getPidPath();

  char buf[1024] = {0};
  char *p = buf;
  size_t size = 0;
  readFromFile(pidFile, p, size);

  std::string temp(p);
  long long target = 0;
  strToVal(temp, target);

  EXPECT_EQ(pid, target);
}