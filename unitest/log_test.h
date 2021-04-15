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
// Created by Longda on 2021
//

#ifndef CTESTLOG_H_
#define CTESTLOG_H_

#include <string>

/*
 *
 */
class LogTest {
public:
  LogTest();
  virtual ~LogTest();

  int init(const std::string &logFile = "test.log");

  void *log_loop(void *param);
};

#endif /* CTESTLOG_H_ */
