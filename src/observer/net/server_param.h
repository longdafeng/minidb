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

#ifndef __SRC_OBSERVER_NET_SERVER_PARAM_H__
#define __SRC_OBSERVER_NET_SERVER_PARAM_H__

class ServerParam {
public:
  ServerParam();

  ServerParam(ServerParam &other);
  ~ServerParam() {}

public:
  // accpet client's address, default is INADDR_ANY, means accept every address
  long listenAddr;

  int maxConnectionNum;
  // server listing port
  int port;
};

#endif //__SRC_OBSERVER_NET_SERVER_PARAM_H__
