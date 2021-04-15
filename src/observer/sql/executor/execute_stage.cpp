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

#include "execute_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/seda/seda_stats_stage.h"
#include "common/seda/timer_stage.h"
#include "event/storage_event.h"

using namespace common;

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::makeStage(const std::string &tag) {
  ExecuteStage *stage = new ExecuteStage(tag.c_str());
  if (stage == NULL) {
    LOG_ERROR("new ExecuteStage failed");
    return NULL;
  }
  stage->setProperties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::setProperties() {
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
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = nextStageList.begin();
  defaultStorageStage = *(stgp++);
  memStorageStage = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handleEvent(StageEvent *event) {
  LOG_TRACE("Enter\n");

  StorageEvent *storageEvent = new StorageEvent(event);
  if (storageEvent == NULL) {
    LOG_ERROR("Failed to new StorageEvent");
    event->doneImmediate();
    return;
  }

  CompletionCallback *cb = new CompletionCallback(this, NULL);
  if (cb == NULL) {
    LOG_ERROR("Failed to new callback for SessionEvent");

    delete storageEvent;
    event->doneImmediate();

    return;
  }

  event->pushCallback(cb);

  defaultStorageStage->handleEvent(storageEvent);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callbackEvent(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // TODO, here finish read all data from disk or network, but do nothing here.
  event->doneImmediate();

  LOG_TRACE("Exit\n");
  return;
}
