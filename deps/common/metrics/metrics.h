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

#ifndef __COMMON_METRICS_METRICS_H__
#define __COMMON_METRICS_METRICS_H__

#include "common/lang/string.h"
#include "common/metrics/metric.h"
#include "common/metrics/snapshot.h"
#include "common/metrics/timer_snapshot.h"
#include "common/metrics/uniform_reservoir.h"
#include <sys/time.h>

namespace common {

class Gauge : public Metric {
public:
  // user implement snapshot function
  void setSnapshot(Snapshot *value) { snapshotValue = value; }
};

class Counter : public Metric {
  void setSnapshot(SnapshotBasic<long> *value) { snapshotValue = value; }
};

class Meter : public Metric {
public:
  Meter();
  virtual  ~Meter();

  void inc(long increase);
  void inc();

  void snapshot();

protected:
  std::atomic<long> value;
  long snapshotTick;
};

// SimpleTimer just get tps and meanvalue
// time unit is ms
class SimpleTimer : public Meter {
public:
  virtual ~SimpleTimer();

  void inc(long increase);

  void update(long one);

  void snapshot();

protected:
  std::atomic<long> times;
};

// Histogram metric is complicated, in normal case ,
//  please skip us histogram or Timer as more as possible
//  try use SimpleTimer to replace them.
//  if use histogram , please use sampling method.
class Histogram : public UniformReservoir {
public:
  Histogram(RandomGenerator &random);
  Histogram(RandomGenerator &random, size_t size);
  virtual ~Histogram();

  void snapshot();

};

// timeunit is ms
// Timer = Histogram + Meter
class Timer : public UniformReservoir {
public:
  Timer(RandomGenerator &random);
  Timer(RandomGenerator &random, size_t size);
  virtual ~Timer();

  void snapshot();
  void update(double ms);

protected:
  std::atomic<long> value;
  long snapshotTick;
};
// update ms
class TimerStat {
public:
  TimerStat(SimpleTimer &st);

  ~TimerStat();
  void start();
  void end();

public:
  SimpleTimer &st;
  long startTick;
  long endTick;
};

} // namespace common
#endif //__COMMON_METRICS_METRICS_H__
