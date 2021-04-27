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

#ifndef __OBSERVER_SESSION_SESSIONEVENT_H__
#define __OBSERVER_SESSION_SESSIONEVENT_H__

#include "common/seda/stage_event.h"
#include "net/connection_context.h"

using namespace common;

class SessionEvent : public StageEvent {
public:
  SessionEvent(ConnectionContext *client);
  virtual ~SessionEvent();

  ConnectionContext *getClient() const;

  char *getResponse() const;
  void setResponse(char *response);
  int getResponseLen() const;
  void setResponseLen(int response_len);
  char *getRequestBuf();
  int getRequestBufLen();

private:
  ConnectionContext *client;

  char *response;
  int responseLen;
};

#endif //__OBSERVER_SESSION_SESSIONEVENT_H__
