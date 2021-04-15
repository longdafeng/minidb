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
#include <stdio.h>
#include <string>
#include <time.h>

#include "print_test.h"

PrintTest::PrintTest() {
  // TODO Auto-generated constructor stub
}

PrintTest::~PrintTest() {
  // TODO Auto-generated destructor stub
}

void PrintTest::printll() {
  time_t now_time;
  time(&now_time);
  unsigned char c = 255;
  long long size64 = c;
  printf("size %d, %lld, %llx, %lld\n", (int)sizeof(size64), size64, size64,
         (long long)now_time);

  int i = -1;
  unsigned long long usize64 = i;
  printf("size %d,%llu,%llx, %d\n", (int)sizeof(usize64), usize64, usize64,
         -10);
}

void PrintTest::printPointer() {
  int i = 10;
  int *p = &i;

  printf("i %p", p);

  // build error
  //    std::string str = "pointer " + p;
  //    printf(str.c_str());

  char pointerBuf[16] = {0};
  sprintf(pointerBuf, "%p", p);
}

void testPrint() {
  PrintTest test;

  test.printPointer();
}

int main(int argc, char **argv) { return 0; }