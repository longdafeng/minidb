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

#include "plan_cache_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/seda/seda_stats_stage.h"
#include "common/seda/timer_stage.h"

using namespace common;

//! Constructor
PlanCacheStage::PlanCacheStage(const char *tag) : Stage(tag) {}

//! Destructor
PlanCacheStage::~PlanCacheStage() {}

//! Parse properties, instantiate a stage object
Stage *PlanCacheStage::makeStage(const std::string &tag) {
  PlanCacheStage *stage = new PlanCacheStage(tag.c_str());
  if (stage == NULL) {
    LOG_ERROR("new PlanCacheStage failed");
    return NULL;
  }
  stage->setProperties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool PlanCacheStage::setProperties() {
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
bool PlanCacheStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = nextStageList.begin();
  executeStage = *(stgp++);
  parseStage = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void PlanCacheStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void PlanCacheStage::handleEvent(StageEvent *event) {
  LOG_TRACE("Enter\n");

  // Add callback to update plan cache
  CompletionCallback *cb = new CompletionCallback(this, NULL);
  if (cb == NULL) {
    LOG_ERROR("Failed to new callback for SQLEvent");
    event->doneImmediate();
    return;
  }

  event->pushCallback(cb);
  // do nothing here, pass the event to the next stage
  parseStage->handleEvent(event);

  LOG_TRACE("Exit\n");
  return;
}

void PlanCacheStage::callbackEvent(StageEvent *event,
                                   CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // TODO  update execute plan here
  event->doneImmediate();

  LOG_TRACE("Exit\n");
  return;
}
