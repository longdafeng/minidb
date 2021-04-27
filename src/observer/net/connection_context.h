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

#ifndef __SRC_OBSERVER_NET_CONNECTION_CONTEXT_H__
#define __SRC_OBSERVER_NET_CONNECTION_CONTEXT_H__

#include <event.h>
#include <ini_setting.h>

typedef struct _ConnectionContext {
  int fd;
  char addr[24];
  char buf[SOCKET_BUFFER_SIZE];
  struct event readEvent;
  pthread_mutex_t mutex;
} ConnectionContext;

#endif //__SRC_OBSERVER_NET_CONNECTION_CONTEXT_H__
