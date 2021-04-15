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

#ifndef __COMMON_IO_ROLL_SELECT_DIR__
#define __COMMON_IO_ROLL_SELECT_DIR__

#include <map>
#include <string>
#include <vector>

#include "common/defs.h"
#include "common/io/select_dir.h"
#include "common/lang/mutex.h"
namespace common {

class RollSelectDir : public SelectDir {
public:
  RollSelectDir() { MUTEX_INIT(&mMutex, NULL); }
  ~RollSelectDir() { MUTEX_DESTROY(&mMutex); }

public:
  /**
   * inherit from CSelectDir
   */
  std::string select();
  void setBaseDir(std::string baseDir);

public:
  std::string mBaseDir;
  std::vector<std::string> mSubdirs;
  pthread_mutex_t mMutex;
  u32_t mPos;
};

} //namespace common
#endif /* __COMMON_IO_ROLL_SELECT_DIR__ */
