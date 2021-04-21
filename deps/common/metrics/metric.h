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

#ifndef __COMMON_METRICS_METRIC_H__
#define __COMMON_METRICS_METRIC_H__

#include "common/metrics/snapshot.h"

namespace common {

class Metric {
public:
  virtual void snapshot() = 0;

  virtual Snapshot *getSnapshot() { return snapshotValue; }

protected:
  Snapshot *snapshotValue;
};

}//namespace common
#endif //__COMMON_METRICS_METRIC_H__
