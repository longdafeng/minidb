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

#include "vector_test.h"
#include <iostream>
#include <vector>

template <class T> void output(std::vector<T> &output) {
  auto it = output.begin();
  for (int i = 0; it != output.end(); it++, i++) {
    std::cout << i << ":" << *it << std::endl;
  }

  std::cout << "!!!!!!!!!!!!" << std::endl;
}

void VectorTest::testConsturct() {
  // constructors used in the same order as described above:
  std::vector<int> first;          // empty vector of ints
  std::vector<int> second(4, 100); // four ints with value 100
  std::vector<int> third(second.begin(),
                         second.end()); // iterating through second
  std::vector<int> fourth(third);       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16, 2, 77, 29};
  std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

  output(second);
}

void VectorTest::testResize() {
  std::vector<int> myvector;

  // set some initial content:
  for (int i = 1; i < 10; i++)
    myvector.push_back(i);

  myvector.resize(5);
  output(myvector);

  myvector.resize(8, 100);
  output(myvector);

  myvector.resize(12);
  output(myvector);
}

void VectorTest::testAccessData() {
  std::vector<int> myvector(5);

  int *p = myvector.data();

  *p = 10;
  ++p;
  *p = 20;
  p[2] = 100;

  output(myvector);
}

void VectorTest::testAssign() {
  std::vector<int> first;
  std::vector<int> second;
  std::vector<int> third;

  first.assign(7, 100); // 7 ints with a value of 100

  std::vector<int>::iterator it;
  it = first.begin() + 1;

  second.assign(it, first.end() - 1); // the 5 central values of first

  int myints[] = {1776, 7, 4};
  third.assign(myints, myints + 3); // assigning from array.

  std::cout << "Size of first: " << int(first.size()) << '\n';
  std::cout << "Size of second: " << int(second.size()) << '\n';
  std::cout << "Size of third: " << int(third.size()) << '\n';
}

void VectorTest::testAllocator() {
  std::vector<int> myvector;
  int *p;
  unsigned int i;

  // allocate an array with space for 5 elements using vector's allocator:
  p = myvector.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i = 0; i < 5; i++)
    myvector.get_allocator().construct(&p[i], i);

  std::cout << "output myvector" << std::endl;
  output(myvector);

  std::cout << "The allocated array contains:";
  for (i = 0; i < 5; i++)
    std::cout << ' ' << p[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i = 0; i < 5; i++)
    myvector.get_allocator().destroy(&p[i]);
  myvector.get_allocator().deallocate(p, 5);
}

void VectorTest::testBoolFlip() {
  std::vector<bool> mask;

  mask.push_back(true);
  mask.push_back(false);
  mask.push_back(false);
  mask.push_back(true);

  //仅支持vector<bool>
  mask.flip();

  std::cout << std::boolalpha;
  std::cout << "mask contains:";
  for (unsigned i = 0; i < mask.size(); i++)
    std::cout << ' ' << mask.at(i);
  std::cout << '\n';
}

void testVector() {
  VectorTest test;

  // test.testConsturct();
  // test.testResize();
  // test.testAccessData();
  // test.testAllocator();
  test.testBoolFlip();
}

int main(int argc, char **argv) { return 0; }
