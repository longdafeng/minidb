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

#include "storage/default/default_storage_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/metrics/metrics_registry.h"

using namespace common;

const std::string DefaultStorageStage::QUERY_METRIC_TAG = "DefaultStorageStage.query";

//! Constructor
DefaultStorageStage::DefaultStorageStage(const char *tag) : Stage(tag) {}

//! Destructor
DefaultStorageStage::~DefaultStorageStage() {}

//! Parse properties, instantiate a stage object
Stage *DefaultStorageStage::makeStage(const std::string &tag) {
  DefaultStorageStage *stage = new DefaultStorageStage(tag.c_str());
  if (stage == NULL) {
    LOG_ERROR("new DefaultStorageStage failed");
    return NULL;
  }
  stage->setProperties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool DefaultStorageStage::setProperties() {
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
bool DefaultStorageStage::initialize() {
  LOG_TRACE("Enter");

  MetricsRegistry &metricsRegistry = theGlobalMetricsRegistry();
  queryMetric =  new SimpleTimer();
  metricsRegistry.registerMetric(QUERY_METRIC_TAG, queryMetric);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void DefaultStorageStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void DefaultStorageStage::handleEvent(StageEvent *event) {
  LOG_TRACE("Enter\n");
  TimerStat timerStat(*queryMetric);

  event->doneImmediate();

  LOG_TRACE("Exit\n");
  return;
}

void DefaultStorageStage::callbackEvent(StageEvent *event,
                                        CallbackContext *context) {
  LOG_TRACE("Enter\n");

  LOG_TRACE("Exit\n");
  return;
}
