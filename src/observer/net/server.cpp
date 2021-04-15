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
// Created by Longda on 2021
//

#include <arpa/inet.h>
#include <errno.h>

#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net/server.h"

#include "common/log/log.h"
#include "common/seda/seda_config.h"
#include "event/session_event.h"
#include "ini_setting.h"

using namespace common;
Stage * Server::sessionStage = NULL;

ServerParam::ServerParam() {
  listenAddr = INADDR_ANY;
  maxConnectionNum = MAX_CONNECTION_NUM_DEFAULT;
  port = PORT_DEFAULT;
}

ServerParam::ServerParam(ServerParam &other) {
  this->listenAddr = other.listenAddr;
  this->maxConnectionNum = other.maxConnectionNum;
  this->port = other.port;
}

Server::Server(ServerParam inputServerParam) : serverParam(inputServerParam) {
  started = false;
  serverSocket = 0;
  baseEvent = NULL;
  listenEv = NULL;
  sessionStage = theSedaConfig()->getStage(SESSION_STAGE_NAME);
}

Server::~Server() {
  if (started == true) {
    shutdown();
  }
}

int Server::setNonblock(int fd) {

  int flags = fcntl(fd, F_GETFL);
  if (flags == -1) {
    LOG_INFO("Failed to get flags of fd :%d. ", fd);
    return -1;
  }

  flags = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  if (flags == -1) {
    LOG_INFO("Failed to set non-block flags of fd :%d. ", fd);
    return -1;
  }
  return 0;
}

void Server::read(int fd, short ev, void *arg) {
  SessionEvent *sev = new SessionEvent((ConnectionContext *)arg);

  sessionStage->addEvent(sev);
}

void Server::accept(int fd, short ev, void *arg) {
  Server *instance = (Server *)arg;
  struct sockaddr_in addr;
  socklen_t addrlen = sizeof(addr);

  int ret = 0;

  int clientFd = ::accept(fd, (struct sockaddr *)&addr, &addrlen);
  if (clientFd < 0) {
    LOG_ERROR("Failed to accept client's connection, %s", strerror(errno));
    return;
  }

  char ipAddr[24];
  if (inet_ntop(AF_INET, &addr.sin_addr, ipAddr, sizeof(ipAddr)) == NULL) {
    LOG_ERROR("Failed to get ip address of client, %s", strerror(errno));
    ::close(clientFd);
    return;
  }

  ret = instance->setNonblock(clientFd);
  if (ret < 0) {
    LOG_ERROR("Failed to set socket of %s as non blocking, %s", ipAddr,
              strerror(errno));
    ::close(clientFd);
    return;
  }

  int yes = 1;
  ret = setsockopt(clientFd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes));
  if (ret < 0) {
    LOG_ERROR("Failed to set socket of %s option as : TCP_NODELAY %s\n", ipAddr,
              strerror(errno));
    ::close(clientFd);
    return;
  }

  ConnectionContext *clientContext = new ConnectionContext();
  memset(clientContext, 0, sizeof(ConnectionContext));
  clientContext->fd = clientFd;
  strncpy(clientContext->ipAddr, ipAddr, sizeof(ipAddr) - 1);

  event_set(&clientContext->readEvent, clientContext->fd, EV_READ | EV_PERSIST,
            read, clientContext);

  ret = event_base_set(instance->baseEvent, &clientContext->readEvent);
  if (ret < 0) {
    LOG_ERROR(
        "Failed to do event_base_set for read event of %s into libevent, %s",
        clientContext->ipAddr, strerror(errno));
    free(clientContext);
    ::close(instance->serverSocket);
    return;
  }

  ret = event_add(&clientContext->readEvent, NULL);
  if (ret < 0) {
    LOG_ERROR("Failed to event_add for read event of %s into libevent, %s",
              clientContext->ipAddr, strerror(errno));
    free(clientContext);
    ::close(instance->serverSocket);
    return;
  }

  LOG_INFO("Accepted connection from %s\n", clientContext->ipAddr);

  return;
}

int Server::start() {
  int ret = 0;
  struct sockaddr_in sa;

  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    LOG_ERROR("socket(): can not create server socket: %s.", strerror(errno));
    return -1;
  }

  int yes = 1;
  ret = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  if (ret < 0) {
    LOG_ERROR("Failed to set socket option of reuse address: %s.",
              strerror(errno));
    ::close(serverSocket);
    return -1;
  }

  ret = setNonblock(serverSocket);
  if (ret < 0) {
    LOG_ERROR("Failed to set socket option non-blocking:%s. ", strerror(errno));
    ::close(serverSocket);
    return -1;
  }

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(serverParam.port);
  sa.sin_addr.s_addr = htonl(serverParam.listenAddr);

  ret = bind(serverSocket, (struct sockaddr *)&sa, sizeof(sa));
  if (ret < 0) {
    LOG_ERROR("bind(): can not bind server socket, %s", strerror(errno));
    ::close(serverSocket);
    return -1;
  }

  ret = listen(serverSocket, serverParam.maxConnectionNum);
  if (ret < 0) {
    LOG_ERROR("listen(): can not listen server socket, %s", strerror(errno));
    ::close(serverSocket);
    return -1;
  }

  listenEv =
      event_new(baseEvent, serverSocket, EV_READ | EV_PERSIST, accept, this);
  if (listenEv == NULL) {
    LOG_ERROR("Failed to create listen event, %s.", strerror(errno));
    ::close(serverSocket);
    return -1;
  }

  ret = event_add(listenEv, NULL);
  if (ret < 0) {
    LOG_ERROR("event_add(): can not add accept event into libevent, %s",
              strerror(errno));
    ::close(serverSocket);
    return -1;
  }

  started = true;
  return 0;
}

int Server::serve() {
  baseEvent = event_base_new();
  if (baseEvent == NULL) {
    LOG_ERROR("Failed to create event base, %s.", strerror(errno));
    exit(-1);
  }

  int retval = start();
  if (retval == -1) {
    LOG_PANIC("Failed to start network");
    exit(-1);
  }

  event_base_dispatch(baseEvent);

  return 0;
}

void Server::shutdown() {
  // cleanup
  event_del(listenEv);
  event_free(listenEv);
  listenEv = NULL;
  event_base_free(baseEvent);
  baseEvent = NULL;

  started = false;
}
