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

using namespace std;

enum Color { red, blue, green, orange, violate };

int main(int argc, char **argv) {
  Color color;
  // color = 3;  //invalid
  // Color color1(3); //invalid

  color = Color(3); // valid
  color = Color(18);
  cout << color << endl;

  int a = 3 + red;

  std::cout << a << std::endl;
}