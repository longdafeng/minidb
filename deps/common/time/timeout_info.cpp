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
// Created by Longda on 2010
//

#include <sys/time.h>

#include "common/time/timeout_info.h"
namespace common {

TimeoutInfo::TimeoutInfo(time_t deadLine)
  : deadline(deadLine), isTimedOut(false), refCnt(0) {
  MUTEX_INIT(&mutex, NULL);
}

TimeoutInfo::~TimeoutInfo() {
  // unlock mutex as we locked it before 'delete this'
  MUTEX_UNLOCK(&mutex);

  MUTEX_DESTROY(&mutex);
}

void TimeoutInfo::attach() {
  MUTEX_LOCK(&mutex);
  refCnt++;
  MUTEX_UNLOCK(&mutex);
}

void TimeoutInfo::detach() {
  MUTEX_LOCK(&mutex);
  if (0 == --refCnt) {
    delete this;
    return;
  }
  MUTEX_UNLOCK(&mutex);
}

bool TimeoutInfo::hasTimedOut() {
  MUTEX_LOCK(&mutex);
  bool ret = isTimedOut;
  if (!isTimedOut) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    ret = isTimedOut = (tv.tv_sec >= deadline);
  }
  MUTEX_UNLOCK(&mutex);

  return ret;
}

} //namespace common