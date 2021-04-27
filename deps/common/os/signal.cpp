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

#include "common/os/signal.h"
#include "common/log/log.h"
#include "pthread.h"
namespace common {

void setSignalHandler(int sig, sighandler_t func) {
  struct sigaction newsa, oldsa;
  sigemptyset(&newsa.sa_mask);
  newsa.sa_flags = 0;
  newsa.sa_handler = func;
  int rc = sigaction(sig, &newsa, &oldsa);
  if (rc) {
    std::cerr << "Failed to set signal " << sig << SYS_OUTPUT_FILE_POS
              << SYS_OUTPUT_ERROR << std::endl;
  }
}

/*
** Set Singal handling Fucntion
*/
void setSignalHandler(sighandler_t func) {
  setSignalHandler(SIGQUIT, func);
  setSignalHandler(SIGHUP, func);
}

void blockDefaultSignals(sigset_t *signal_set, sigset_t *old_set) {
  sigemptyset(signal_set);
#ifndef DEBUG
  // SIGINT will effect our gdb debugging
  sigaddset(signal_set, SIGINT);
#endif
  sigaddset(signal_set, SIGTERM);
  sigaddset(signal_set, SIGUSR1);
  pthread_sigmask(SIG_BLOCK, signal_set, old_set);
}

void unBlockDefaultSignals(sigset_t *signal_set, sigset_t *old_set) {
  sigemptyset(signal_set);
#ifndef DEBUG
  sigaddset(signal_set, SIGINT);
#endif
  sigaddset(signal_set, SIGTERM);
  sigaddset(signal_set, SIGUSR1);
  pthread_sigmask(SIG_UNBLOCK, signal_set, old_set);
}

void *waitForSignals(void *args) {
  LOG_INFO("Start thread to wait signals.");
  sigset_t *signal_set = (sigset_t *)args;
  int sig_number = -1;
  while (true) {
    errno = 0;
    int ret = sigwait(signal_set, &sig_number);
    LOG_INFO("sigwait return value: %d, %d \n", ret, sig_number);
    if (ret != 0)  {
      char errstr[256];
      strerror_r(errno, errstr, sizeof(errstr));
      LOG_ERROR("error (%d) %s\n", errno, errstr);
    }
  }
  return NULL;
}

void startWaitForSignals(sigset_t *signal_set) {
  pthread_t pThread;
  pthread_attr_t pThreadAttrs;

  // create all threads as detached.  We will not try to join them.
  pthread_attr_init(&pThreadAttrs);
  pthread_attr_setdetachstate(&pThreadAttrs, PTHREAD_CREATE_DETACHED);

  pthread_create(&pThread, &pThreadAttrs, waitForSignals, (void *)signal_set);

}
} // namespace common