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

#ifndef __COMMON_METRICS_REPORTER_H__
#define __COMMON_METRICS_REPORTER_H__

#include <string>
#include "common/metrics/metric.h"

namespace common {


class Reporter {
public:
  virtual void report(const std::string &tag, Metric *metric) = 0;
};
} // namespace Reporter
#endif //__COMMON_METRICS_REPORTER_H__
