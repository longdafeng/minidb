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

void waitForSignals(sigset_t *signal_set, int &sig_number) {
  while (true) {
    errno = 0;
    int ret = sigwait(signal_set, &sig_number);
    LOG_DEBUG("sigwait return value: %d \n", ret);
    if (ret == 0) {
      LOG_INFO("signal caught: %d\n", sig_number);
      break;
    } else {
      char errstr[256];
      strerror_r(errno, errstr, sizeof(errstr));
      LOG_ERROR("error (%d) %s\n", errno, errstr);
    }
  }
}

void waitForSignals(sigset_t *signal_set) {
  int sig_number;
  waitForSignals(signal_set, sig_number);
}

} //namespace common