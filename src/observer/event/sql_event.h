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
// Created by Longda on 2021/4/14.
//

#ifndef __OBSERVER_SQL_EVENT_SQLEVENT_H__
#define __OBSERVER_SQL_EVENT_SQLEVENT_H__

#include "common/seda/stage_event.h"
#include <string>

class SQLEvent : public common::StageEvent {
public:
  SQLEvent(StageEvent *event, std::string &sql);
  virtual ~SQLEvent();

private:
  std::string sql;
  void *context;
  StageEvent *sessionEvent;
};

#endif //__SRC_OBSERVER_SQL_EVENT_SQLEVENT_H__
