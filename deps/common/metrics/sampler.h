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

#ifndef __COMMON_METRICS_SAMPLER_H__
#define __COMMON_METRICS_SAMPLER_H__

#include "common/math/random_generator.h"

namespace common {


/**
 * The most simple sample function
 */
class Sampler {
public:
  Sampler();
  virtual ~Sampler();

  bool sampling();

  void setRatio(double ratio);
  double getRatio();

private:
  double ratio;
  int ratioNum;
  RandomGenerator random;
};

Sampler *&theGlobalSampler();
} //namespace common
#endif //__COMMON_METRICS_SAMPLER_H__
