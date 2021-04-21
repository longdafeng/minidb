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
// Created by Longda on 2021/4/19.
//

#ifndef __COMMON_METRICS_RESERVOIR_H_
#define __COMMON_METRICS_RESERVOIR_H_

#include <stdint.h>

#include "common/math/random_generator.h"
#include "common/metrics/metric.h"
#include "common/metrics/snapshot.h"



namespace common {

class Reservoir : public Metric {
public:
  Reservoir(RandomGenerator &random);
  virtual ~Reservoir();

public:
  virtual size_t size() = 0;
  virtual int getCount() = 0;

  virtual void update(double one) = 0;

  virtual void reset() = 0;

protected:
  virtual int next(int range);

private:
  RandomGenerator &random;
};

} // namespace common

#endif /* __COMMON_METRICS_RESERVOIR_H_ */
