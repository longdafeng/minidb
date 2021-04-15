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

#ifndef __OBSERVER_SQL_EVENT_STORAGEEVENT_H__
#define __OBSERVER_SQL_EVENT_STORAGEEVENT_H__

#include "common/seda/stage_event.h"

class StorageEvent : public common::StageEvent {
public:
  StorageEvent(common::StageEvent *sqlEvent);
  virtual ~StorageEvent();

private:
  common::StageEvent *sqlEvent;
};

#endif //__OBSERVER_SQL_EVENT_STORAGEEVENT_H__
