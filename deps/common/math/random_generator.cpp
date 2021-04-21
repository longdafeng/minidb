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
// Created by Longda on 2021/4/20.
//




#include <chrono>

#include "common/math/random_generator.h"

namespace common {

RandomGenerator::RandomGenerator()
    : randomData(std::chrono::system_clock::now().time_since_epoch().count()) {}

RandomGenerator::~RandomGenerator() {}

unsigned int RandomGenerator::next() {


  return randomData();
}

unsigned int RandomGenerator::next(unsigned int range) {
  if (range > 0) {
    return next() % range;
  } else {
    return 0;
  }
}

}//namespace common