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
// Created by Longda on 2021/5/3.
//


#include "init.h"
#include "ini_setting.h"

#include "common/conf/ini.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/math/math.h"
#include "common/os/path.h"
#include "common/os/pidfile.h"
#include "common/os/process.h"
#include "common/os/signal.h"
#include "common/seda/init.h"
#include "common/seda/stage_factory.h"

#include "common/metrics/log_reporter.h"
#include "common/metrics/metrics_registry.h"
#include "session/session_stage.h"
#include "sql/executor/execute_stage.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/parser/parse_stage.h"
#include "sql/parser/resolve_stage.h"
#include "sql/plan_cache/plan_cache_stage.h"
#include "sql/query_cache/query_cache_stage.h"
#include "storage/default/default_storage_stage.h"
#include "storage/mem/mem_storage_stage.h"

using namespace common;

bool *&_getInit() {
  static bool util_init = false;
  static bool *util_init_p = &util_init;
  return util_init_p;
}

bool getInit() { return *_getInit(); }

void setInit(bool value) {
  *_getInit() = value;
  return;
}

void sigHandler(int sig) {
  // TODO Signal handler will be add in the next step.
  //  Add action to shutdown

  LOG_INFO("Receive one signal of %d.", sig);

  return;
}

int initLog(ProcessParam *pProcessCfg, Ini &gProperties) {
  const std::string &procName = pProcessCfg->getProcessName();
  try {
    // we had better alloc one lock to do so, but simplify the logic
    if (gLog) {
      return 0;
    }

    const std::string logSectionName = "LOG";
    std::map<std::string, std::string> logSection =
        gProperties.get(logSectionName);

    std::string logFileName;

    // get log file name
    std::string key = "LOG_FILE_NAME";
    std::map<std::string, std::string>::iterator it = logSection.find(key);
    if (it == logSection.end()) {
      logFileName = procName + ".log";
      std::cout << "Not set log file name, use default " << logFileName
                << std::endl;
    } else {
      logFileName = it->second;
    }

    logFileName = getAboslutPath(logFileName.c_str());

    LOG_LEVEL logLevel = LOG_LEVEL_INFO;
    key = ("LOG_FILE_LEVEL");
    it = logSection.find(key);
    if (it != logSection.end()) {
      int log = (int)logLevel;
      strToVal(it->second, log);
      logLevel = (LOG_LEVEL)log;
    }

    LOG_LEVEL consoleLevel = LOG_LEVEL_INFO;
    key = ("LOG_CONSOLE_LEVEL");
    it = logSection.find(key);
    if (it != logSection.end()) {
      int log = (int)consoleLevel;
      strToVal(it->second, log);
      consoleLevel = (LOG_LEVEL)log;
    }

    LoggerFactory::initDefault(logFileName, logLevel, consoleLevel);

    key = ("DefaultLogModules");
    it = logSection.find(key);
    if (it != logSection.end()) {
      gLog->SetDefaultModule(it->second);
    }

    if (pProcessCfg->isDemon()) {
      sysLogRedirect(logFileName.c_str(), logFileName.c_str());
    }

    return 0;
  } catch (std::exception &e) {
    std::cerr << "Failed to init log for " << procName << SYS_OUTPUT_FILE_POS
              << SYS_OUTPUT_ERROR << std::endl;
    return errno;
  }

  return 0;
}

void cleanupLog() {

  if (gLog) {
    delete gLog;
    gLog = NULL;
  }
  return;
}

int prepareInitSeda() {
  static StageFactory sessionStageFactory("SessionStage",
                                          &SessionStage::makeStage);
  static StageFactory resolveStageFactory("ResolveStage",
                                          &ResolveStage::makeStage);
  static StageFactory queryCacheStageFactory("QueryCacheStage",
                                             &QueryCacheStage::makeStage);
  static StageFactory parseStageFactory("ParseStage", &ParseStage::makeStage);
  static StageFactory planCacheFactory("PlanCacheStage",
                                       &PlanCacheStage::makeStage);
  static StageFactory optimizeFactory("OptimizeStage",
                                      &OptimizeStage::makeStage);
  static StageFactory executeFactory("ExecuteStage", &ExecuteStage::makeStage);
  static StageFactory defaultStorageFactory("DefaultStorageStage",
                                            &DefaultStorageStage::makeStage);
  static StageFactory memStorageFactory("MemStorageStage",
                                        &MemStorageStage::makeStage);
}

int init(ProcessParam *processParam) {

  if (getInit()) {

    return 0;
  }

  setInit(true);

  // Run as daemon if daemonization requested
  int rc = STATUS_SUCCESS;
  if (processParam->isDemon()) {
    rc = daemonizeService(processParam->getStdOut().c_str(),
                          processParam->getStdErr().c_str());
    if (rc != 0) {
      std::cerr << "Shutdown due to failed to daemon current process!"
                << std::endl;
      return rc;
    }
  }

  writePidFile(processParam->getProcessName().c_str());

  // Initialize global variables before enter multi-thread mode
  // to avoid race condition
  theSwVersion();

  // Read Configuration files
  rc = theGlobalProperties()->load(processParam->getConf());
  if (rc) {
    std::cerr << "Failed to load configuration files" << std::endl;
    return rc;
  }

  // Init tracer
  rc = initLog(processParam, *theGlobalProperties());
  if (rc) {
    std::cerr << "Failed to init Log" << std::endl;
    return rc;
  }

  std::string confData;
  theGlobalProperties()->toString(confData);
  LOG_INFO("Output configuration \n%s", confData.c_str());

  // seda is used for backend async event handler
  // the latency of seda is slow, it isn't used for critical latency
  // environment.
  prepareInitSeda();
  rc = initSeda(processParam);
  if (rc) {
    LOG_ERROR("Failed to init seda configuration!");
    return rc;
  }

  LogReporter *logReporter = theGlobalLogReporter();
  MetricsRegistry &metricsRegistry = theGlobalMetricsRegistry();

  metricsRegistry.addReporter(logReporter);

  // Block interrupt signals before creating child threads.
  setSignalHandler(sigHandler);
  // sigset_t newSigset, oset;
  // blockDefaultSignals(&newSigset, &oset);
  //  wait interrupt signals
  // startWaitForSignals(&newSigset);

  seedRandom();

  LOG_INFO("Successfully init utility");

  return STATUS_SUCCESS;
}

void cleanupUtil() {

  if (NULL != theGlobalProperties()) {
    delete theGlobalProperties();
    theGlobalProperties() = NULL;
  }

  LOG_INFO("Shutdown Cleanly!");

  // Finalize tracer
  cleanupLog();

  setInit(false);
  return;
}

void cleanup() {}
