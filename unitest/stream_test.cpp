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

#include "stream_test.h"
#include <iostream>

StreamTest::StreamTest() {}

StreamTest::~StreamTest() {}

void StreamTest::testSimple() {

  // std::cout << ("test me %u", (unsigned int)-32) << std::endl; // this will
  // lead to compiling warning

  std::cout << "test me " << ((unsigned int)-32) << std::endl;

  double a[9] = {0.0};

  std::cout << a << std::endl;

  int len = 10;
  const char *str = "12345678901234567890";

  printf("asdfasdf : %.*s", len, str);
}

int main(int argc, char **argv) {
  StreamTest test;

  test.testSimple();
}