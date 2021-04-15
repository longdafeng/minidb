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

void test_simple() {
  int a = 939;
  const int b = 784;
  const int *p1 = &a; // 常量指针
  //*p1 = b;  // invalid
  p1 = &b; // valid

  // int * p2 = &b; // invalid, 不可以把一个常量地址赋给非常量指针；
  // int **pp1 = &p1; // invalid, 不可以把一个常量地址赋给非常量指针；
  const int array[] = {1, 2, 3, 4};
  // int **pp1 = &array; // invalid, 不可以把一个常量地址赋给非常量指针；

  int *const p3 = &a; //指针常量
  *p3 = 879;          // read-only variable is not assignable
  // p3 = &b;    //invalid

  // just avoid compile warning
  std::cout << p1 << std::endl;
  std::cout << array << std::endl;
}

int sum_array(int *a, int b) {
  int sum = 0;
  for (int i = 0; i < b; ++i) {
    sum += *(a + i);
  }
  return sum;
}

void test_const_array() {
  const int array[] = {1, 2, 3, 4};
  // sum_array(array, sizeof(array) / sizeof(array[0]));// invalid,
  // 不可以把一个常量地址赋给非常量指针；

  std::cout << array << std::endl;
}

int main(int argc, char **argv) { test_simple(); }
