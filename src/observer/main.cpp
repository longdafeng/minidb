// __CR__
// Copyright (c) 2008-2012 LongdaFeng
// All Rights Reserved
//
// This software contains the intellectual property of LongdaFeng
// or is licensed to LongdaFeng from third parties.  Use of this
// software and the intellectual property contained therein is
// expressly limited to the terms and conditions of the License Agreement
// under which it is provided by or on behalf of LongdaFeng.
// __CR__

/*
 * StructureTest.cpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Longda Feng
 */


#include <unistd.h>
#include <iostream>

#include "init.h"
#include "common/os/process.h"
#include "net/server.h"
#include "net/server_param.h"

using namespace common;

#define NET "NET"

void usage() {
  // TODO ADD USAGE
  std::cout << "Useage " << std::endl;
}

void parseParameter(int argc, char **argv) {
  std::string processName = getProcessName(argv[0]);

  ProcessParam *processParam = theProcessParam();

  processParam->initDefault(processName);

  // Process args
  int opt;
  extern char *optarg;
  while ((opt = getopt(argc, argv, "ds:f:o:e:h")) > 0) {
    switch (opt) {
    case 'f':
      processParam->setConf(optarg);
      break;
    case 'o':
      processParam->setStdOut(optarg);
      break;
    case 'e':
      processParam->setStdErr(optarg);
      break;
    case 'd':
      processParam->setDemon(true);
      break;
    case 'h':
    default:
      usage();
      return;
    }
  }

  return;
}

Server *initServer() {
  std::map<std::string, std::string> netSection =
      theGlobalProperties()->get(NET);

  long listenAddr = INADDR_ANY;
  long maxConnectionNum = MAX_CONNECTION_NUM_DEFAULT;
  int port = PORT_DEFAULT;

  std::map<std::string, std::string>::iterator it =
      netSection.find(CLIENT_ADDRESS);
  if (it != netSection.end()) {
    std::string str = it->second;
    strToVal(str, listenAddr);
  }

  it = netSection.find(MAX_CONNECTION_NUM);
  if (it != netSection.end()) {
    std::string str = it->second;
    strToVal(str, maxConnectionNum);
  }

  it = netSection.find(PORT);
  if (it != netSection.end()) {
    std::string str = it->second;
    strToVal(str, port);
  }

  ServerParam serverParam;
  serverParam.listenAddr = listenAddr;
  serverParam.maxConnectionNum = maxConnectionNum;
  serverParam.port = port;

  Server *server = new Server(serverParam);

  return server;
}

int main(int argc, char **argv) {
  parseParameter(argc, argv);

  int rc = STATUS_SUCCESS;
  rc = init(theProcessParam());
  if (rc) {
    std::cerr << "Shutdown due to failed to init!" << std::endl;
    cleanup();
    return rc;
  }

  Server *server = initServer();
  server->serve();

  cleanup();
}
