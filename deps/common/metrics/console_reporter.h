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

#ifndef __COMMON_METRICS_CONSOLE_REPORTER_H__
#define __COMMON_METRICS_CONSOLE_REPORTER_H__

#include "common/metrics/reporter.h"

namespace common {


class ConsoleReporter : public Reporter {
public:
  void report(const std::string &tag, Metric *metric);
};

ConsoleReporter* theGlobalConsoleReporter();
} //namespace common
#endif //__COMMON_METRICS_CONSOLE_REPORTER_H__
