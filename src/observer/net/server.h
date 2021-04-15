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
// Created by Longda on 2021/4/1.
//

#ifndef __OBSERVER_NET_SERVER_H__
#define __OBSERVER_NET_SERVER_H__

#include "common/defs.h"

#include "common/seda/stage.h"
#include "net/connection_context.h"
#include "net/server_param.h"

class Server {
public:
  Server(ServerParam inputServerParam);
  ~Server();

  int serve();
  void shutdown();

private:
  // close connection
  static void closeConnection(ConnectionContext *clientContext);

  int setNonblock(int fd);

  //
  static void read(int fd, short ev, void *arg);

  static void accept(int fd, short ev, void *arg);

  int start();

private:
  bool started;

  int serverSocket;
  struct event_base *baseEvent;
  struct event *listenEv;

  ServerParam serverParam;

  static common::Stage *sessionStage;
};

#endif //__OBSERVER_NET_SERVER_H__
