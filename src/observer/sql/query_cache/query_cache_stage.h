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

#ifndef __OBSERVER_SQL_QUERY_CACHE_STAGE_H__
#define __OBSERVER_SQL_QUERY_CACHE_STAGE_H__

#include "common/seda/stage.h"

class QueryCacheStage : public common::Stage {
public:
  ~QueryCacheStage();
  static Stage *makeStage(const std::string &tag);

protected:
  // common function
  QueryCacheStage(const char *tag);
  bool setProperties();

  bool initialize();
  void cleanup();
  void handleEvent(common::StageEvent *event);
  void callbackEvent(common::StageEvent *event,
                     common::CallbackContext *context);

protected:
private:
  Stage *planCacheStage;
};

#endif //__OBSERVER_SQL_QUERY_CACHE_STAGE_H__
