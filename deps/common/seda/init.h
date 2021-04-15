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

#ifndef __COMMON_SEDA_INIT_H__
#define __COMMON_SEDA_INIT_H__

// Basic includes
#include <assert.h>
#include <iostream>
#include <set>
#include <signal.h>
#include <sstream>
#include <string>
#include <vector>

#include "common/conf/ini.h"
#include "common/defs.h"
#include "common/os/process_param.h"
namespace common {



/**
 * start the seda process, do this will trigger all threads
 */
int initSeda(ProcessParam *pProcessCfg);

void cleanupSeda();

} //namespace common
#endif // __COMMON_SEDA_INIT_H__
