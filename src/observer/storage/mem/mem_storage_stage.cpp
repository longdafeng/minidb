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

#include "mem_storage_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/seda/seda_stats_stage.h"
#include "common/seda/timer_stage.h"

using namespace common;

//! Constructor
MemStorageStage::MemStorageStage(const char *tag) : Stage(tag) {}

//! Destructor
MemStorageStage::~MemStorageStage() {}

//! Parse properties, instantiate a stage object
Stage *MemStorageStage::makeStage(const std::string &tag) {
  MemStorageStage *stage = new MemStorageStage(tag.c_str());
  if (stage == NULL) {
    LOG_ERROR("new MemStorageStage failed");
    return NULL;
  }
  stage->setProperties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool MemStorageStage::setProperties() {
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
bool MemStorageStage::initialize() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void MemStorageStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void MemStorageStage::handleEvent(StageEvent *event) {
  LOG_TRACE("Enter\n");

  event->doneImmediate();

  LOG_TRACE("Exit\n");
  return;
}

void MemStorageStage::callbackEvent(StageEvent *event,
                                    CallbackContext *context) {
  LOG_TRACE("Enter\n");

  LOG_TRACE("Exit\n");
  return;
}
