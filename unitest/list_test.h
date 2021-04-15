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

#ifndef CTESTLIST_H_
#define CTESTLIST_H_

#include <iostream>
#include <list>

/*
 *
 */
class ListTest {
public:
  ListTest();
  virtual ~ListTest();

  template <class T> void output(std::list<T> &output);

  void testRemove();

  void testConstructor();

  void testAssign();

  void testEmplaceFront();

  void testInsert();

  void testSlice();

  void testUnique();

  void testMerge();

  void testSwap();
};

#endif /* CTESTLIST_H_ */
