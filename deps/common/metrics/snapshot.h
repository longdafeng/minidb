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

#ifndef __COMMON_METRICS_SNAPSHOT_H__
#define __COMMON_METRICS_SNAPSHOT_H__

#include <string>
#include "common/lang/string.h"

namespace common {


class Snapshot {
public:
  virtual ~Snapshot() {};
  virtual std::string toString() = 0;
};

template <class T>
class SnapshotBasic : public Snapshot {
public:
  SnapshotBasic(){

  };

  virtual ~SnapshotBasic() {}

  void setValue(T &input) { value = input; }

  std::string toString() {
    std::string ret;
    valToStr(value, ret);
    return ret;
  }

private:
  T value;
};

class SimplerTimerSnapshot: public  Snapshot{
public:
   SimplerTimerSnapshot() {

  }

  virtual ~SimplerTimerSnapshot() {}

  void setValue(double mean, double tps) {
    this->mean = mean;
    this->tps = tps;
  }

  std::string toString() {
    std::stringstream oss;
    oss << "mean:" << mean << ",tps:"<<tps;

    return oss.str();
  }
private:
  double mean;
  double tps;
};
} //namespace common
#endif //__COMMON_METRICS_SNAPSHOT_H__
