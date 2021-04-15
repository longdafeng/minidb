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

#include "process_param.h"
#include <assert.h>
namespace common {

//! Global process config
ProcessParam*& theProcessParam()
{
  static ProcessParam* processCfg = new ProcessParam();

  return processCfg;
}

void ProcessParam::initDefault(std::string &processName) {
  assert(processName.empty() == false);
  this->processName = processName;
  if (stdOut.empty() == true) {
    stdOut = "../log/" + processName + ".out";
  }
  if (stdErr.empty() == true) {
    stdErr = "../log/" + processName + ".err";
  }
  if (conf.empty() == true) {
    conf = "../etc/" + processName + ".ini";
  }

  demon = false;
}



} //namespace common