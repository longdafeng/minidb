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
#ifndef __COMMON_METRICS_UNIFORM_RESERVOIR_H_
#define __COMMON_METRICS_UNIFORM_RESERVOIR_H_

#include <atomic>
#include <vector>
#include <pthread.h>

#include "common/metrics/reservoir.h"

namespace common {

/**
 * A random sampling reservoir of a stream of {@code long}s. Uses Vitter's
 * Algorithm R to produce a statistically representative sample.
 *
 * @see <a href="http://www.cs.umd.edu/~samir/498/vitter.pdf">Random Sampling
 * with a Reservoir</a>
 */

class UniformReservoir : public Reservoir {
public:
  UniformReservoir(RandomGenerator &random);
  UniformReservoir(RandomGenerator &random, size_t size);
  virtual ~UniformReservoir();

public:
  size_t size();  // data buffer size
  int getCount(); // how many items have been insert?

  void update(double one);
  void snapshot();

  void reset();

protected:
  void init(size_t size);

protected:
  pthread_mutex_t mutex;
  int counter; // counter is likely to be bigger than data.size()
  std::vector<double> data;
  RandomGenerator random;
};

} // namespace common

#endif /* __COMMON_METRICS_UNIFORM_RESERVOIR_H_ */
