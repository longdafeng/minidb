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
#include "type_test.h"
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

void testChar() {
  char c = 'q';
  char16_t w = u'q';
  char32_t l = U'q';
  char16_t w2 = 0x7788;
  char32_t l2 = 0x77778888;

  cout << sizeof(w) << ", " << sizeof(l) << endl;
  cout << (int)c << endl;
  cout << w << endl;
  cout << l << endl;
  cout << w2 << endl;
  cout << l2 << endl;
}

void testFloat() {
  float f = 2.52e-4;
  float f1 = 20.52e4;

  cout << sizeof(f) << endl;
  cout << f1 << endl;

  cout.setf(ios_base::fixed, ios_base::floatfield);
  float f2 = 10.0 / 3.0f;
  double d2 = 10.0 / 3.0;
  long double ld2 = 10.0L / 3.0;
  const float million = 1e6;

  cout << sizeof(f2) << "," << sizeof(d2) << ", " << sizeof(ld2) << endl;

  cout << f2 << endl;
  cout << d2 << endl;
  cout << ld2 << endl;
  cout << million * f2 << endl;
  cout << million * d2 << endl;
  cout << million * ld2 << endl;
}

void testUnsign() {
  int i = -100;
  unsigned int u = 10;

  cout << (unsigned int)i << endl;
  // singed will convert to unsigned type, except char
  cout << i * u << endl;

  signed char sc = -1;
  char c = -1;
  unsigned char uc = -1;

  cout << (int)sc << endl;
  cout << (int)c << endl;
  cout << (int)uc << endl;
}

void testGetline() {
  const int LEN = 5;
  char buffer1[LEN] = {};
  char buffer2[LEN] = {};
  char buffer3[LEN] = {};
  string str;

  cout << "input:" << endl;
  cin >> buffer1;
  //回车符留在队列中，如果没有被读出来，会导致下一个cin 无法读出
  cin.get();
  cout << "input2:" << endl;
  cin.getline(buffer2, LEN);
  //如果输入的字符超过len, 多余的字符会传递给下一个输入
  cin.clear();
  cout << "input3:" << endl;
  cin.get(buffer3, LEN).get();
  cout << "input4:" << endl;
  getline(cin, str);

  cout << strlen(buffer1) << ", " << buffer1 << endl;
  cout << "switch" << endl;
  cout << strlen(buffer2) << ", " << buffer2 << endl;
  cout << "switch" << endl;
  cout << strlen(buffer3) << ", " << buffer3 << endl;
  cout << str.size() << ", " << str << endl;
  cout << "end" << endl;
}

int testWhile() {
  char ch;
  int count = 0;

  cout << "Please input the string:" << endl;
  while (cin.get(ch).fail() == false) {
    if (isalpha(ch)) {
      cout << "is a alpha:";
      cout.put(ch);
    } else if (isspace(ch)) {
      cout << "is a space";
    } else if (isdigit(ch)) {
      cout << "digitial";
    } else if (ispunct(ch)) {
      cout << "is punct";
    } else {
      cout << "unknow:";
      cout.put(ch);
    }
    cout << endl;
    count++;
  }

  cout << endl << count << endl;

  return 0;
}

void testSwitch() {
  char ch;
  int count = 0;

  cout << "Please input the string:" << endl;
  while (cin.get(ch).fail() == false) {

    switch (ch) {
    case 'a':
      cout << "Get a" << endl;
      break;
    // case c:   //wrong
    case 'b':
      cout << "must be const/enum, no variable" << endl;
      break;
    default:
      break;
    }

    cout << endl;
    count++;
  }

  cout << endl << count << endl;
}

int TypeTest::getM() const { return m; }

TypeTest::TypeTest(int m) : m(m) {}

void testAuto() {
  TypeTest type;

  cout << type.getM() << endl;
}

int main(int argc, char **argv) {
  // testChar();
  // testFloat();
  // testUnsign();
  // testGetline();
  // testWhile();
  testAuto();
}
