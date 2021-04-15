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

#include <regex.h>
#include <stdlib.h>
#include <sys/types.h>

#include "common/math/regex.h"
namespace common {

int regex_match(const char *str_, const char *pat_) {
  regex_t reg;
  if (regcomp(&reg, pat_, REG_EXTENDED | REG_NOSUB))
    return -1;

  int ret = regexec(&reg, str_, 0, NULL, 0);
  regfree(&reg);
  return ret;
}

} //namespace common