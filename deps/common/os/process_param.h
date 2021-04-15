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

#ifndef __COMMON_OS_PROCESS_PARAM_H__
#define __COMMON_OS_PROCESS_PARAM_H__

#include <string>
#include <vector>
namespace common {

class ProcessParam {

 public:
  ProcessParam() {}

  virtual ~ProcessParam() {}

  void initDefault(std::string &processName);

  const std::string &getStdOut() const { return stdOut; }

  void setStdOut(const std::string &stdOut) { ProcessParam::stdOut = stdOut; }

  const std::string &getStdErr() const { return stdErr; }

  void setStdErr(const std::string &stdErr) { ProcessParam::stdErr = stdErr; }

  const std::string &getConf() const { return conf; }

  void setConf(const std::string &conf) { ProcessParam::conf = conf; }

  const std::string &getProcessName() const { return processName; }

  void setProcessName(const std::string &processName) {
    ProcessParam::processName = processName;
  }

  bool isDemon() const { return demon; }

  void setDemon(bool demon) { ProcessParam::demon = demon; }

  const std::vector<std::string> &getArgs() const { return args; }

  void setArgs(const std::vector<std::string> &args) {
    ProcessParam::args = args;
  }

 private:
  std::string stdOut;            // The output file
  std::string stdErr;            // The err output file
  std::string conf;              // The configuration file
  std::string processName;       // The process name
  bool demon;                    // whether demon or not
  std::vector<std::string> args; // arguments
};

ProcessParam*& theProcessParam();

} //namespace common
#endif //__COMMON_OS_PROCESS_PARAM_H__
