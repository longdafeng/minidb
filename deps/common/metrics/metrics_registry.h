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

#ifndef __COMMON_METRICS_METRICS_REGISTRY_H__
#define __COMMON_METRICS_METRICS_REGISTRY_H__

#include <string>
#include <map>
#include <list>

#include "common/metrics/metric.h"
#include "common/metrics/reporter.h"

namespace common {

class MetricsRegistry {
public:
  MetricsRegistry() {};
  virtual ~MetricsRegistry(){};

  void registerMetric(const std::string &tag, Metric *metric);
  void unregister(const std::string &tag);

  void snapshot();

  void report();

  void addReporter(Reporter *reporter) {
    reporters.push_back(reporter);
  }


protected:
  std::map<std::string, Metric *> metrics;
  std::list<Reporter *> reporters;


};

MetricsRegistry& theGlobalMetricsRegistry();
}//namespace common
#endif //__COMMON_METRICS_METRICS_REGISTRY_H__
