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
#ifndef CTESTMAP_H_
#define CTESTMAP_H_

#include <map>
#include <string>

/*
 *
 */
class MapTest {
public:
  MapTest();
  virtual ~MapTest();

  void testFind();

  void outputMap(std::map<std::string, std::string> simpleMap);

  void testFindChange();

  void simpleSet();
};

#endif /* CTESTMAP_H_ */
