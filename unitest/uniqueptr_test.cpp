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

#include "uniqueptr_test.h"
#include <iostream>
#include <memory>

void test1() {
  std::unique_ptr<int> p1 = std::unique_ptr<int>(new int(101));

  std::cout << "Before:" << *p1 << std::endl;

  std::unique_ptr<int> p2 = std::move(p1);

  std::cout << "After: " << *p2 << std::endl;

  if (p1) {
    std::cout << "After, p1: " << *p1 << std::endl;
  } else {
    std::cout << "After, p1 release: " << std::endl;
  }
}

void UniquePtrTest::test() { test1(); }

int main(int argc, char **argv) { return 0; }