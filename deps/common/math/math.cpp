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

#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "common/math/math.h"
namespace common {

long int lrandom(const long int scope) {
  srandom(time(0));
  long int ret = 0;
  long int randNum = 0;
  if (scope < (RAND_MAX / 10)) {
    // if scope is bigger than RAND_MAX/10, the precision is not good
    randNum = random();
    ret = randNum % scope;
  } else {
    randNum = (long int)((((double)scope) / RAND_MAX) * random());
    // due to convert scope/RAND_MAX to double, it will lose precision,
    // randNum is possibly bigger scope
    ret = randNum % scope;
  }

  return ret;
}

void seedRandom() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  srand(tv.tv_usec);
}

} //namespace common