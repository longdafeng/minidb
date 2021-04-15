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

#include "common/math/md5.h"
#include "md5_test.h"

using namespace common;

Md5Test::Md5Test() {
  // TODO Auto-generated constructor stub
}

Md5Test::~Md5Test() {
  // TODO Auto-generated destructor stub
}

void Md5Test::string() {
  char buf[512] = "/home/fastdfs/longda";
  unsigned char digest[16] = {0};
  MD5String(buf, digest);
  for (int i = 0; i < 16; i++) {
    printf("%d: %02x %d\n", i, digest[i], digest[i]);
  }
}

int main(int argc, char **argv) {
  Md5Test test;
  test.string();

  return 0;
}
