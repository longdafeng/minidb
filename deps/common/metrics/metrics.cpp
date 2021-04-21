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

#include "common/metrics/metrics.h"
#include "common/lang/mutex.h"

namespace common {
Meter::Meter() {
  struct timeval startTime;
  gettimeofday(&startTime, NULL);

  snapshotTick = startTime.tv_sec * 1000000 + startTime.tv_usec;
  value.store(0l);
}

Meter::~Meter() {
  if (snapshotValue != NULL) {
    delete snapshotValue;
    snapshotValue = NULL;
  }
}

void Meter::inc(long increase) { value.fetch_add(increase); }
void Meter::inc() { inc(1l); }

void Meter::snapshot() {
  // TODO lock here

  struct timeval now;
  gettimeofday(&now, NULL);

  long nowTick = now.tv_sec * 1000000 + now.tv_usec;

  double tempValue =
      (double)value.exchange(0l) / ((snapshotTick - nowTick) / 1000000);
  snapshotTick = nowTick;

  if (snapshotValue == NULL) {
    snapshotValue = new SnapshotBasic<double>();
  }
  ((SnapshotBasic<double> *)snapshotValue)->setValue(tempValue);
}

SimpleTimer::~SimpleTimer() {
  if (snapshotValue != NULL) {
    delete snapshotValue;
    snapshotValue = NULL;
  }
}

void SimpleTimer::inc(long increase) {
  value.fetch_add(increase);
  times++;
}

void SimpleTimer::update(long one) { inc(one); }

void SimpleTimer::snapshot() {

  // TODO lock here
  struct timeval now;
  gettimeofday(&now, NULL);

  long nowTick = now.tv_sec * 1000000 + now.tv_usec;

  long valueSnapshot = value.exchange(0l);
  long timesSnapshot = times.exchange(0l);

  double tps = 0;
  double mean = 0;

  if (timesSnapshot > 0) {
    tps = (double)valueSnapshot / ((snapshotTick - nowTick) / 1000000);
    mean = (double)valueSnapshot / timesSnapshot;
  }

  snapshotTick = nowTick;

  if (snapshotValue == NULL) {
    snapshotValue = new SimplerTimerSnapshot();
  }
  ((SimplerTimerSnapshot *)snapshotValue)->setValue(mean, tps);
}

Histogram::Histogram(RandomGenerator &random) : UniformReservoir(random) {}

Histogram::Histogram(RandomGenerator &random, size_t size)
    : UniformReservoir(random, size) {}

Histogram::~Histogram() {

}

void Histogram::snapshot() {
  UniformReservoir::snapshot();
}

Timer::Timer(RandomGenerator &random)
    : UniformReservoir(random){
  struct timeval startTime;
  gettimeofday(&startTime, NULL);

  snapshotTick = startTime.tv_sec * 1000000 + startTime.tv_usec;
  value.store(0l);
}

Timer::Timer(RandomGenerator &random, size_t size)
    : UniformReservoir(random, size){
  struct timeval startTime;
  gettimeofday(&startTime, NULL);

  snapshotTick = startTime.tv_sec * 1000000 + startTime.tv_usec;
  value.store(0l);
}

Timer::~Timer() {
  if (snapshotValue == NULL) {
    delete snapshotValue;
    snapshotValue = NULL;
  }
}

void Timer::update(double ms) {
  UniformReservoir::update(ms);
  value.fetch_add(1l);
}

void Timer::snapshot() {
  if (snapshotValue == NULL) {
    snapshotValue = new TimerSnapshot();
  }
  TimerSnapshot *timerSnapshot = (TimerSnapshot *)snapshotValue;

  struct timeval now;
  gettimeofday(&now, NULL);

  long nowTick = now.tv_sec * 1000000 + now.tv_usec;

  double tps =
      (double)value.exchange(0l) / ((snapshotTick - nowTick) / 1000000);
  snapshotTick = nowTick;

  MUTEX_LOCK(&mutex);
  std::vector<double> output = data;
  MUTEX_UNLOCK(&mutex);

  timerSnapshot->setCollection(output);
  timerSnapshot->setTps(tps);
}

TimerStat::TimerStat(SimpleTimer &otherST)
    : st(otherST), startTick(0), endTick(0) {

  start();
}

TimerStat::~TimerStat() {
  if (endTick == 0) {
    end();
  }

  st.update((endTick - startTick) / 1000);
}

void TimerStat::start() {
  struct timeval now;
  gettimeofday(&now, NULL);

  startTick = now.tv_sec * 1000000 + now.tv_usec;
}

void TimerStat::end() {
  struct timeval now;
  gettimeofday(&now, NULL);

  endTick = now.tv_sec * 1000000 + now.tv_usec;
}

} // namespace common