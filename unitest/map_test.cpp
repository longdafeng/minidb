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
#include <set>

#include "map_test.h"

MapTest::MapTest() {
  // TODO Auto-generated constructor stub
}

MapTest::~MapTest() {
  // TODO Auto-generated destructor stub
}

void MapTest::testFind() {
  std::map<std::string, std::string> simpleMap;
  std::map<std::string, std::string>::iterator it;

  std::string key = "check";
  it = simpleMap.find(key);
  if (it == simpleMap.end()) {
    std::cout << "find nothing" << std::endl;
  }
}

void MapTest::outputMap(std::map<std::string, std::string> simpleMap) {
  for (std::map<std::string, std::string>::iterator it = simpleMap.begin();
       it != simpleMap.end(); it++) {
    std::cout << "key:" << it->first << ",values:" << it->second << std::endl;
  }
}

void MapTest::testFindChange() {
  std::map<std::string, std::string> simpleMap;
  std::map<std::string, std::string>::iterator it;

  simpleMap.insert(std::pair<std::string, std::string>("happy", "sky"));

  it = simpleMap.find("happy");
  if (it != simpleMap.end()) {
    it->second = "happysky";
  }

  outputMap(simpleMap);
}

void MapTest::simpleSet() {
  std::map<std::string, std::set<std::string>> simpleMap;

  std::set<std::string> &data = simpleMap["one"];

  data.insert("simple set");

  for (std::map<std::string, std::set<std::string>>::iterator it =
           simpleMap.begin();
       it != simpleMap.end(); it++) {
    std::cout << it->first << std::endl;
    for (std::set<std::string>::iterator iit = it->second.begin();
         iit != it->second.end(); iit++) {
      std::cout << *iit << std::endl;
    }
  }
}

void testMap() {
  MapTest test;
  // test.testFind();
  // test.testFindChange();
  test.simpleSet();
}

int main(int argc, char **argv) {
  testMap();
  return 0;
}