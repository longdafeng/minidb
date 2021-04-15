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

#include <iostream>
#include <unistd.h>

#include "process_test.h"

ProcessTest::ProcessTest() {
  // TODO Auto-generated constructor stub
}

ProcessTest::~ProcessTest() {
  // TODO Auto-generated destructor stub
}

int ProcessTest::fork() {
  pid_t pid = fork();
  int sleepTime = 1000;
  if (pid > 0) {
    std::cout << "create one son process " << ((unsigned int)pid) << std::endl;

    while (sleepTime-- > 0) {
      sleep(1);
    }
  } else if (pid == 0) {
    printf("Enter son process");
    while (sleepTime-- > 0) {
      sleep(1);
    }
  }
  return 0;
}

int main(int argc, char **argv) { return 0; }