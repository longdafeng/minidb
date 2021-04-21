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

#include <string>
#include <iostream>
#include "common/metrics/metric.h"
#include "common/metrics/console_reporter.h"



namespace common {

ConsoleReporter* theGlobalConsoleReporter() {
  static ConsoleReporter* instance = new ConsoleReporter();

  return instance;
}

 void ConsoleReporter::report(const std::string &tag, Metric *metric) {
  Snapshot *snapshot = metric->getSnapshot();

  if (snapshot != NULL) {
    printf("%s:%s\n", tag.c_str(), snapshot->toString().c_str());
  }else {
    printf("There is no snapshot of %s metrics.", tag.c_str());
  }
}

}// namespace common