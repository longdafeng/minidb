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

#include "session_event.h"
SessionEvent::SessionEvent(ConnectionContext *client) : client(client) {
  response = NULL;
  responseLen = 0;
}

SessionEvent::~SessionEvent() {

  if (response != NULL) {
    delete response;
    response = NULL;
    responseLen = 0;
  }
}

ConnectionContext *SessionEvent::getClient() const { return client; }

char *SessionEvent::getResponse() const { return response; }

void SessionEvent::setResponse(char *response) {
  SessionEvent::response = response;
}

int SessionEvent::getResponseLen() const { return responseLen; }

void SessionEvent::setResponseLen(int response_len) {
  responseLen = response_len;
}

char *SessionEvent::getRequestBuf() { return client->buf; }

int SessionEvent::getRequestBufLen() { return SOCKET_BUFFER_SIZE; }