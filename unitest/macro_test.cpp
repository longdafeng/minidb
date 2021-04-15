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
// Created by Longda on 2021
//
#include <stdio.h>

#define NUM_ONE 1
#define NUM_TWO 2

#define STR1(R) #R
#define STR2(R) STR1(R)

#define NUM_STR (STR2(NUM_ONE) "." STR2(NUM_TWO))

int function() { return 1; }

#define mycro()                                                                \
  ({                                                                           \
    int result = function();                                                   \
    result;                                                                    \
  })

int main(int argc, char **argv) {
  int i = mycro();
  printf("i:%d", i);
  mycro();

  printf("%s", NUM_STR);
}