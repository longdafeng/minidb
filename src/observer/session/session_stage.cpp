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
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/seda/seda_stats_stage.h"
#include "common/seda/timer_stage.h"

#include "common/seda/callback.h"
#include "event/session_event.h"
#include "event/sql_event.h"

//! Constructor
SessionStage::SessionStage(const char *tag) : Stage(tag), resolveStage(NULL) {}

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

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void SessionStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void SessionStage::handleEvent(StageEvent *event) {
  LOG_TRACE("Enter\n");

  // right now, we just support only one event.
  readSocket(event);

  LOG_TRACE("Exit\n");
  return;
}

void SessionStage::callbackEvent(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");
  SessionEvent *sev = dynamic_cast<SessionEvent *>(event);
  ConnectionContext *client = sev->getClient();

  int dataLen = sev->getResponseLen();
  int wlen = 0;
  for (int i = 0; i < 3 && wlen < dataLen; i++) {
    int len = write(client->fd, sev->getResponse(), sev->getResponseLen());
    if (len < 0) {
      LOG_ERROR("Failed to send data back to client\n");
      sev->done();
      return;
    }
    wlen += len;
  }
  if (wlen < dataLen) {
    LOG_WARN("Not all data has been send back to client");
  }

  sev->done();
  LOG_TRACE("Exit\n");
  return;
}

void SessionStage::closeConnection(ConnectionContext *clientContext) {
  event_del(&clientContext->readEvent);
  ::close(clientContext->fd);
  free(clientContext);
}

void SessionStage::readSocket(StageEvent *event) {
  SessionEvent *sev = dynamic_cast<SessionEvent *>(event);
  ConnectionContext *client = sev->getClient();
  int len;

  //会把参数fd 所指的文件传送count个字节到buf指针所指的内存中
  len = ::read(client->fd, sev->getRequestBuf(),
               sizeof(sev->getRequestBufLen()));
  if (len == 0) {
    /* 客户端断开连接，在这里移除读事件并且释放客户数据结构 */
    LOG_INFO("Disconnected\n");
    closeConnection(client);
    sev->done();
    return;
  } else if (len < 0) {
    /* 出现了其它的错误，在这里关闭socket，移除事件并且释放客户数据结构 */
    LOG_ERROR("Failed to read socket of %s, %s\n", client->ipAddr,
              strerror(errno));
    closeConnection(client);
    sev->done();
    return;
  }

  std::string sql = sev->getRequestBuf();
  SQLEvent *sqlEvent = new SQLEvent(sev, sql);
  if (sqlEvent == NULL) {
    LOG_ERROR("Failed to new SQLEvent");
    closeConnection(client);
    sev->done();
    return;
  }

  CompletionCallback *cb = new CompletionCallback(this, NULL);
  if (cb == NULL) {
    LOG_ERROR("Failed to new callback for SessionEvent");

    delete sqlEvent;
    sev->done();

    closeConnection(client);
    return;
  }

  sev->pushCallback(cb);

  resolveStage->handleEvent(sqlEvent);

  // TODO it will write data directly
}
