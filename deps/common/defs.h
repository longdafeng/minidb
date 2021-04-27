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

#ifndef __COMMON_DEFS_H__
#define __COMMON_DEFS_H__

#include <errno.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/version.h"
namespace common {

#ifndef gettid
#if defined(__MACH__)
#define gettid() ((long long)pthread_self())
#elif defined(LINUX)
#define gettid() ((long long)pthread_self())
#endif

#endif

inline const std::string &theSwVersion() {
  static const std::string swVersion(VERSION_STR);

  return swVersion;
}

enum {
  // General Error Codes
  STATUS_SUCCESS = 0,   //!< Success status should be zero,
  STATUS_INVALID_PARAM, //!< Invalid parameter
  STATUS_FAILED_INIT,   //!< Failed to init program
  STATUS_PROPERTY_ERR,  //!< Property error
  STATUS_INIT_LOG,      //!< log error
  STATUS_INIT_THREAD,   //!< failed to init thread
  STATUS_FAILED_JOB,    //!< Failed to do job
  STATUS_FAILED_NETWORK, //!< Network failure

  STATUS_UNKNOW_ERROR,
  STATUS_LAST_ERR //!< last error code

};

const unsigned int ONE_KILO = 1024;
const unsigned int ONE_MILLION = ONE_KILO * ONE_KILO;
const unsigned int ONE_GIGA = ONE_MILLION * ONE_KILO;
const unsigned int FILENAME_LENGTH_MAX = 256; // the max filename length

static const char FILE_PATH_SPLIT = '/';
static const char FILE_PATH_SPLIT_STR[] = "/";

/*
 * Define types
 *
 */
typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long long u64_t;

typedef char s8_t;
typedef short s16_t;
typedef int s32_t;
typedef long long s64_t;


#define LOCAL_HOST "localhost"

} //namespace common
#endif //__COMMON_DEFS_H__
