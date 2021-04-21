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

#include <sstream>
#include "common/metrics/timer_snapshot.h"

namespace common {

TimerSnapshot::TimerSnapshot() {}

TimerSnapshot::~TimerSnapshot() {}

double TimerSnapshot::getTps() { return tps; }

void TimerSnapshot::setTps(double tps) { this->tps = tps; }

std::string TimerSnapshot::toString() {
  std::stringstream oss;

  oss << HistogramSnapShot::toString() << ",tps:" << tps;

  return oss.str();
}
} // namespace common