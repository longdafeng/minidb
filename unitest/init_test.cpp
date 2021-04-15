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

#include <iostream>

class Cstatic {
public:
  static int a;
  int b;
  Cstatic(int b) {
    this->b = b;
    std::cout << "static init " << a++ << " b:" << b << std::endl;
  }
};

class Afather {
public:
  int a;
  static Cstatic c1;
  Afather() {
    a = 1;
    std::cout << "Father init " << std::endl;
  }
};

class Bson : public Afather {
public:
  int b;
  int c;
  static Cstatic c2;
  Bson() {
    b = 2;
    std::cout << "Bson init" << std::endl;
  }
};

int Cstatic::a = 0;

// chCstatic Bson::c2 = Cstatic(2);

int main(int argc, char **argv) {
  // Bson *bson = new Bson();

  // std::cout << "bson class member default value is " << bson->c << std::endl;

  // std::cout << "bson class member default value is " << Bson::c2.b <<
  // std::endl;
}