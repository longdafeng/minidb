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

#include "common/metrics/sampler.h"
#include "common/log/log.h"

#define RANGE_SIZE 100

namespace common {

Sampler *&theGlobalSampler() {
  static Sampler *gSampler = new Sampler();

  return gSampler;
}

Sampler::Sampler():random() {}

Sampler::~Sampler() {}

bool Sampler::sampling() {
  int v = random.next(100);
  if (v <= ratioNum) {
    return true;
  } else {
    return false;
  }
}

double Sampler::getRatio() { return ratio; }

void Sampler::setRatio(double ratio) {
  if (0 <= ratio && ratio <= 1) {
    this->ratio = ratio;
    ratioNum = ratio * RANGE_SIZE;
  } else {
    LOG_WARN("Invalid ratio :%lf", ratio);
  }
}

}//namespace common

