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

#include "session_stage.h"

#include "common/conf/ini.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"

#include "common/lang/mutex.h"
#include "common/metrics/metrics_registry.h"
#include "common/seda/callback.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "net/server.h"

const std::string SessionStage::SQL_METRIC_TAG = "SessionStage.sql";

//! Constructor
SessionStage::SessionStage(const char *tag)
    : Stage(tag), resolveStage(NULL), sqlMetric(NULL) {}

//! Destructor
SessionStage::~SessionStage() {}

//! Parse properties, instantiate a stage object
Stage *SessionStage::makeStage(const std::string &tag) {
  SessionStage *stage = new SessionStage(tag.c_str());
  if (stage == NULL) {
    LOG_ERROR("new ExecutorStage failed");
    return NULL;
  }
  stage->setProperties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool SessionStage::setProperties() {
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
bool SessionStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = nextStageList.begin();
  resolveStage = *(stgp++);

  MetricsRegistry &metricsRegistry = theGlobalMetricsRegistry();
  sqlMetric = new SimpleTimer();
  metricsRegistry.registerMetric(SQL_METRIC_TAG, sqlMetric);
  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void SessionStage::cleanup() {
  LOG_TRACE("Enter");

  MetricsRegistry &metricsRegistry = theGlobalMetricsRegistry();
  if (sqlMetric != NULL) {
    metricsRegistry.unregister(SQL_METRIC_TAG);
    delete sqlMetric;
    sqlMetric = NULL;
  }

  LOG_TRACE("Exit");
}

void SessionStage::handleEvent(StageEvent *event) {
  LOG_TRACE("Enter\n");

  // right now, we just support only one event.
  handleRequest(event);

  LOG_TRACE("Exit\n");
  return;
}

void SessionStage::callbackEvent(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  SessionEvent *sev = dynamic_cast<SessionEvent *>(event);


  Server::send(sev->getClient(), sev->getResponse(), sev->getResponseLen());
  //Server::send(sev->getClient(), sev->getRequestBuf(), strlen(sev->getRequestBuf()));

  sev->done();
  LOG_TRACE("Exit\n");
  return;
}

void SessionStage::handleRequest(StageEvent *event) {

  SessionEvent *sev = dynamic_cast<SessionEvent *>(event);

  TimerStat sqlStat(*sqlMetric);
  std::string sql = sev->getRequestBuf();

  CompletionCallback *cb = new CompletionCallback(this, NULL);
  if (cb == NULL) {
    LOG_ERROR("Failed to new callback for SessionEvent");

    sev->done();
    return;
  }

  sev->pushCallback(cb);

  resolveStage->handleEvent(sev);

  // TODO it will write data directly
}
