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

#include "common/log/log.h"

#include "common/seda/callback.h"
#include "common/seda/stage.h"
#include "common/seda/stage_event.h"
namespace common {

extern bool &theEventHistoryFlag();

/**
 * @author Longda
 * @date   3/27/07
 *
 * Implementation of CompletionCallback class.
 */

//! Constructor
CompletionCallback::CompletionCallback(Stage *trgt, CallbackContext *ctx)
  : targetStage(trgt), context(ctx), nextCb(NULL),
    evHistFlag(theEventHistoryFlag()) {}

//! Destructor
CompletionCallback::~CompletionCallback() {
  if (context) {
    delete context;
  }
  if (nextCb) {
    delete nextCb;
  }
}

//! Push onto a callback stack
void CompletionCallback::pushCallback(CompletionCallback *next) {
  ASSERT((!nextCb), "%s", "cannot push a callback twice");

  nextCb = next;
}

//! Pop off of a callback stack
CompletionCallback *CompletionCallback::popCallback() {
  CompletionCallback *retVal = nextCb;

  nextCb = NULL;
  return retVal;
}

//! One event is complete
void CompletionCallback::eventDone(StageEvent *ev) {

  if (evHistFlag) {
    ev->saveStage(targetStage, StageEvent::CALLBACK_EV);
  }
  targetStage->callbackEvent(ev, context);
}

//! Reschedule callback on target stage thread
void CompletionCallback::eventReschedule(StageEvent *ev) {
  targetStage->addEvent(ev);
}

void CompletionCallback::eventTimeout(StageEvent *ev) {
  LOG_DEBUG("to call eventTimeout for stage %s", targetStage->getName());
  if (evHistFlag) {
    ev->saveStage(targetStage, StageEvent::TIMEOUT_EV);
  }
  targetStage->timeoutEvent(ev, context);
}

} //namespace common