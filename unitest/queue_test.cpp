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

#include "queue_test.h"

#include <iostream>
#include <queue>

QueueTest::QueueTest() {
  // TODO Auto-generated constructor stub
}

QueueTest::~QueueTest() {
  // TODO Auto-generated destructor stub
}

void QueueTest::testEmptyFront() {
  std::queue<int *> queue;

  int *a = queue.front();

  std::cout << a << std::endl;
}

void testQueue() {
  QueueTest test;
  test.testEmptyFront();
}

int main(int argc, char **argv) { return 0; }