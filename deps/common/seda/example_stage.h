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

#ifndef __COMMON_SEDA_EXAMPLE_STAGE_H__
#define __COMMON_SEDA_EXAMPLE_STAGE_H__

#include "common/seda/stage.h"

namespace common {

class ExampleStage : public Stage {
public:
  ~ExampleStage();
  static Stage *makeStage(const std::string &tag);

protected:
  // common function
  ExampleStage(const char *tag);
  bool setProperties();

  bool initialize();
  void cleanup();
  void handleEvent(StageEvent *event);
  void callbackEvent(StageEvent *event, CallbackContext *context);

protected:
private:
};
} // namespace common
#endif //__COMMON_SEDA_EXAMPLE_STAGE_H__
