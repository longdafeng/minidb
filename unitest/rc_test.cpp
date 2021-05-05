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
// Created by Longda on 2021/5/3.
//
#include "rc.h"
#include <iostream>

int main(int argc, char **argv) {
  RC status = RC::BUFFERPOOL_EOF;

  std::cout << rc2SimpleStr(status) << std::endl ;
}