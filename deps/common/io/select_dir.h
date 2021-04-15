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

#ifndef __COMMON_IO_SELECT_DIR_H__
#define __COMMON_IO_SELECT_DIR_H__

#include <string>
namespace common {

class SelectDir {
public:
  virtual std::string select() { return std::string(""); };
  virtual void setBaseDir(std::string baseDir){};
};

} //namespace common
#endif /* __COMMON_IO_SELECT_DIR_H__ */
