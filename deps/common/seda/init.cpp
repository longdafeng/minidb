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
// Created by Longda on 2010
//

#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <paths.h>
#include <pthread.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/time/datetime.h"

#include "common/seda/init.h"
#include "common/seda/kill_thread.h"
#include "common/seda/seda_config.h"
#include "common/seda/seda_stats_stage.h"
#include "common/seda/stage_factory.h"
#include "common/seda/thread_pool.h"
#include "common/seda/timer_stage.h"
namespace common {


int initSeda(ProcessParam *pProcessCfg) {
  // Initialize the static data structures of threadpool
  Threadpool::createPoolKey();

  // initialize class factory instances here
  static StageFactory killThreadFactory("KillThreads",
                                        &KillThreadStage::makeStage);
  static StageFactory timerFactory("TimerStage", &TimerStage::makeStage);
  static StageFactory sedaStatsFactory("SedaStatsStage",
                                       &SedaStatsStage::makeStage);

  // try to parse the seda configuration files
  SedaConfig *config = SedaConfig::getInstance();
  SedaConfig::status_t configStat;

  configStat = config->parse();
  if (configStat != SedaConfig::SUCCESS) {
    LOG_ERROR("Error: unable to parse file %s",
              pProcessCfg->getProcessName().c_str());
    return errno;
  }

  // Log a message to indicate that we are restarting, when looking
  // at a log we can see if mmon is restarting us because we keep
  // crashing.
  LOG_INFO("(Re)Starting State: Pid: %u Time: %s", (unsigned int)getpid(),
           DateTime::now().toStringLocal().c_str());
  LOG_INFO("The process Name is %s", pProcessCfg->getProcessName().c_str());

  // try to initialize the seda configuration
  configStat = config->init();
  if (configStat != SedaConfig::SUCCESS) {
    LOG_ERROR("SedaConfig: unable to initialize seda stages");
    return errno;
  }

  theSedaConfig() = config;

  return 0;
}

void cleanupSeda() {
  SedaConfig *sedaConfig = SedaConfig::getInstance();
  delete sedaConfig;
  SedaConfig::getInstance() = NULL;
}

} //namespace common