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

#ifndef __COMMON_SEDA_STAGE_FACTORY_H__
#define __COMMON_SEDA_STAGE_FACTORY_H__

#include "common/seda/class_factory.h"
#include "common/seda/stage.h"
namespace common {


class Stage;

typedef ClassFactory<Stage> StageFactory;

} //namespace common
#endif // __COMMON_SEDA_STAGE_FACTORY_H__
