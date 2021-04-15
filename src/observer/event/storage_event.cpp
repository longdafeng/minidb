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

#include "storage_event.h"

StorageEvent::StorageEvent(common::StageEvent *otherSqlEvent)
    : sqlEvent(otherSqlEvent) {}

StorageEvent::~StorageEvent() {
  if (sqlEvent != NULL) {
    sqlEvent->done();
    sqlEvent = NULL;
  }
}