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

#ifndef __COMMON_METRICS_HISTOGRAM_SNAPSHOT_H_
#define __COMMON_METRICS_HISTOGRAM_SNAPSHOT_H_

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "common/metrics/snapshot.h"

namespace common {

class HistogramSnapShot : public Snapshot {
public:
  HistogramSnapShot();
  explicit HistogramSnapShot(const std::vector<double> &collection);
  virtual ~HistogramSnapShot();

public:
  void setCollection(const std::vector<double> &collection);

  /**
   * Returns the value at the given quantile
   *
   * @param quantile a given quantile, in {@code [0..1]}
   * @return the value in the distribute
   */
  double getValue(double quantile);

  /**
   * Returns the size of collection in the snapshot
   */
  size_t size() const;

  /**
   * Returns 50th_percentile.
   */
  double getMedian();

  double get75th();
  double get90th();
  double get95th();
  double get99th();
  double get999th();

  double getMax();
  double getMin();
  double getMean();

  const std::vector<double> &getValues();

  std::string toString();
protected:
  std::vector<double> data;
};

} // namespace common

#endif /* __COMMON_METRICS_HISTOGRAM_SNAPSHOT_H_ */
