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
// Include Files
#include <assert.h>

#include "common/seda/kill_thread.h"
#include "common/seda/thread_pool.h"
namespace common {


//! Notify the pool and kill the thread
/**
 * @param[in] event Pointer to event that must be handled.
 *
 * @post  Call never returns.  Thread is killed.  Pool is notified.
 */
void KillThreadStage::handleEvent(StageEvent *event) {
  getPool()->threadKill();
  event->done();
  this->releaseEvent();
  pthread_exit(0);
}

//! Process properties of the classes
/**
 * @pre class members are uninitialized
 * @post initializing the class members
 * @return the class object
 */
Stage *KillThreadStage::makeStage(const std::string &tag) {
  return new KillThreadStage(tag.c_str());
}

bool KillThreadStage::setProperties() {
  // nothing to do
  return true;
}

} //namespace common