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
// Created by Longda on 2021/4/13.
//

#include <string.h>
#include <string>

#include "optimize_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"

using namespace common;

//! Constructor
OptimizeStage::OptimizeStage(const char *tag) : Stage(tag) {}

//! Destructor
OptimizeStage::~OptimizeStage() {}

//! Parse properties, instantiate a stage object
Stage *OptimizeStage::makeStage(const std::string &tag) {
  OptimizeStage *stage = new OptimizeStage(tag.c_str());
  if (stage == NULL) {
    LOG_ERROR("new OptimizeStage failed");
    return NULL;
  }
  stage->setProperties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool OptimizeStage::setProperties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool OptimizeStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = nextStageList.begin();
  executeStage = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void OptimizeStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void OptimizeStage::handleEvent(StageEvent *event) {
  LOG_TRACE("Enter\n");

  // TODO optimize sql plan, here just pass the event to the next stage
  executeStage->handleEvent(event);

  LOG_TRACE("Exit\n");
  return;
}

void OptimizeStage::callbackEvent(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  LOG_TRACE("Exit\n");
  return;
}
