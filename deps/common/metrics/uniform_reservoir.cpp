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

#include <stdint.h>
#include "common/metrics/uniform_reservoir.h"
#include "common/lang/mutex.h"
#include "common/metrics/histogram_snapshot.h"

namespace common {

#define DEFAULT_SIZE 1023

UniformReservoir::UniformReservoir(RandomGenerator &random)
    : Reservoir(random), counter(0) {
  pthread_mutexattr_t mutexatr;
  pthread_mutexattr_init(&mutexatr);
  pthread_mutexattr_settype(&mutexatr, PTHREAD_MUTEX_RECURSIVE);

  MUTEX_INIT(&mutex, &mutexatr);

  init(DEFAULT_SIZE);
}

UniformReservoir::UniformReservoir(RandomGenerator &random, size_t size)
    : Reservoir(random), counter(0) {

  pthread_mutexattr_t mutexatr;
  pthread_mutexattr_init(&mutexatr);
  pthread_mutexattr_settype(&mutexatr, PTHREAD_MUTEX_RECURSIVE);

  MUTEX_INIT(&mutex, &mutexatr);
  init(size);
}

UniformReservoir::~UniformReservoir() {
  if (snapshotValue == NULL) {
    delete snapshotValue;
    snapshotValue = NULL;
  }
}

void UniformReservoir::init(size_t size) {
  MUTEX_LOCK(&mutex);
  counter = 0;
  data.resize(size);
  MUTEX_UNLOCK(&mutex);
}

size_t UniformReservoir::size() {
  MUTEX_LOCK(&mutex);
  size_t size = (counter < data.size()) ? counter : data.size();
  MUTEX_UNLOCK(&mutex);
  return size;
}

int UniformReservoir::getCount() {
  MUTEX_LOCK(&mutex);
  int ret = counter;
  MUTEX_UNLOCK(&mutex);
  return ret;
}

void UniformReservoir::update(double value) {
  MUTEX_LOCK(&mutex);
  double count = ++counter;

  if (count < data.size()) {
    data[count] = (value);
  } else {
    double rcount = next(data.size());
    data[rcount] = (value);
  }

  MUTEX_UNLOCK(&mutex);
}

void UniformReservoir::snapshot() {
  MUTEX_LOCK(&mutex);
  std::vector<double> output = data;
  MUTEX_UNLOCK(&mutex);

  if (snapshotValue == NULL) {
    snapshotValue = new HistogramSnapShot();
  }
  ((HistogramSnapShot *)snapshotValue)->setCollection(output);
}

void UniformReservoir::reset() {

  MUTEX_LOCK(&mutex);
  counter = 0;
  data.clear();

  // TODO clear snapshot
  MUTEX_UNLOCK(&mutex);
}

} // namespace common