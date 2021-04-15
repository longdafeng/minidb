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

#ifndef __COMMON_OS_SIGNAL_H__
#define __COMMON_OS_SIGNAL_H__

#include <signal.h>

namespace common {

//! Default function that blocks signals.
/**
 * Now it blocks SIGINT, SIGTERM, and SIGUSR1
 */
void blockDefaultSignals(sigset_t *signal_set, sigset_t *old_set);
//! Default function that unblocks signals.
/**
 * It unblocks SIGINT, SIGTERM,and SIGUSR1.
 */
void unBlockDefaultSignals(sigset_t *signal_set, sigset_t *old_set);

void waitForSignals(sigset_t *signal_set, int &sig_number);
void waitForSignals(sigset_t *signal_set);

// Set signal handling function
/**
 * handler function
 */
typedef void (*sighandler_t)(int);
void setSignalHandler(sighandler_t func);
void setSignalHandler(int sig, sighandler_t func);

} //namespace common
#endif /* __COMMON_OS_SIGNAL_H__ */
