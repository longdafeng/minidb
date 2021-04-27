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

#ifndef __OBSERVER_SESSION_SESSIONSTAGE_H__
#define __OBSERVER_SESSION_SESSIONSTAGE_H__

#include "common/seda/stage.h"
#include "net/connection_context.h"
#include "common/metrics/metrics.h"

class SessionStage : public common::Stage {
public:
  ~SessionStage();
  static Stage *makeStage(const std::string &tag);

protected:
  // common function
  SessionStage(const char *tag);
  bool setProperties();

  bool initialize();
  void cleanup();
  void handleEvent(common::StageEvent *event);
  void callbackEvent(common::StageEvent *event,
                     common::CallbackContext *context);

protected:
  void handleInput(common::StageEvent *event);


  void handleRequest(common::StageEvent *event);

private:
  Stage *resolveStage;



  common::SimpleTimer *sqlMetric;
  static const std::string SQL_METRIC_TAG;

};

#endif //__OBSERVER_SESSION_SESSIONSTAGE_H__
