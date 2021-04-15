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

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "string_test.h"

StringTest::StringTest() {
  // TODO Auto-generated constructor stub
}

StringTest::~StringTest() {
  // TODO Auto-generated destructor stub
}

void mySplitFunction(char *data) {

  double setpoints[8] = {0.0};
  uint8_t count = 0;

  // Split string on comma (,)
  // Convert to double
  char *tokenStr;
  char *rest = data;
  double tmp;
  while ((tokenStr = strtok_r(rest, ",", &rest)) != NULL) {
    tmp = atof(tokenStr);
    setpoints[count] = tmp;
    count++;
    printf("%s\n", tokenStr);
  }

  std::cout << setpoints << std::endl;
}

char *split_by_index(char *s, const char *sep, int index) {
  char *ptr = s;
  char *end = nullptr;
  ptr = strtok_r(ptr, sep, &end);

  for (int i = 0; i < index && ptr != nullptr; i++) {
    ptr = strtok_r(nullptr, sep, &end);
  }

  return ptr;
}

int StringTest::strtok() {
  char str[] = "- This, a sample string.";
  char *pch;
  printf("Splitting string %s \"%s\" into tokens:\n", str, str);
  pch = ::strtok(str, " ,.-");
  while (pch != NULL) {
    printf("%s:%s\n", pch, pch);
    pch = ::strtok(NULL, " ,.-");
  }

  char testString[] = "0.0,1.0";
  printf("%s\n", testString); // returns "0.0,0.0"
  mySplitFunction(testString);
  printf("%s\n", testString); // returns "0.0"

  printf("%03d%010d", -3, -400);
  char myBuf[256] = "asdfasd";
  sprintf(myBuf, "%d", -12345345);
  std::cout << myBuf << std::endl;

  for (int i = 0; i < 10; i++) {
    long a = random();
    std::cout << a << std::endl;
  }
  double negData = 0.0;
  double zeroData = 0.0;
  sscanf("-1024.00", "%lf", &negData);
  sscanf("0.00", "%lf", &zeroData);
  if (zeroData == 0) {
    std::cout << "zero" << std::endl;
  }
  std::cout << "\n\n" << negData << " " << zeroData << std::endl;

  char sprintfBuf[256] = {0};

  sprintf(sprintfBuf, "%s_%03d%010d", "20883011517309910156", 0, 0);
  std::cout << sprintfBuf << std::endl;
  return 0;
}

int StringTest::find() {
  std::string msg("enterprise,20882012455427600156,20110429,1,1=2011-04-29\n2="
                  "1\n3=790742.00\n4=60\n6945=-485.29");
  std::string nameSpace;
  std::string userId;
  std::string date;
  std::string info;

  size_t begin = 0;
  size_t end = 0;

  end = msg.find(MESSAGE_SEP);
  if (end == std::string::npos) {
    return -1;
  }

  nameSpace = msg.substr(begin, end - begin);

  begin = end + 1;
  end = msg.find(MESSAGE_SEP, begin);
  if (end == std::string::npos) {
    return -1;
  }

  userId = msg.substr(begin, end - begin);

  begin = end + 1;
  end = msg.find(MESSAGE_SEP, begin);
  if (end == std::string::npos) {
    return -1;
  }

  date = msg.substr(begin, end - begin);

  begin = end + 1;
  end = msg.find(MESSAGE_SEP, begin);
  if (end == std::string::npos) {
    return -1;
  }

  atoi(msg.substr(begin, end - begin).c_str());

  begin = end + 1;
  info = msg.substr(begin);

  return 0;
}

int StringTest::testAdd() {
  int num = 65;
  std::string a = "adsf";

  // 这个地方并不是得到 a = "adsf,test10", 而是a ="adsf" +
  // ",test"向后偏移10个字节的字符串，这个地方是未知的
  a += ",test";
  a +=
      num; // string 的operator +函数, 是将int 转成char 来计算了，不是转义成“10”
  std::cout << a.c_str() << std::endl;

  char array[5] = {0};
  char array2[3][5] = {{0}};

  //    char *p[] = {array2[0], array2[1], array2[2]};
  //    char (*p2)[5] = &array;

  //    char *p[] = {array2[0], array2[1], array2[2]};
  //    char (*p2)[5] = array;

  //    char *p[] = {array2 + 0, array2 + 1, array2 + 2};
  //    char (*p2)[5] = &array;

  //    char *p[] = {array2 + 0, array2 + 1, array2 + 2};
  //    char (*p2)[5] = array;

  // avoid warning
  std::cout << array << std::endl;
  std::cout << array2 << std::endl;

  return 0;
}

void StringTest::testConstruct() {
  std::string s0("Initial string");

  // constructors used in the same order as described above:
  std::string s1;
  std::string s2(s0);
  std::string s3(s0, 8, 3);
  std::string s4("A character sequence");
  std::string s5("Another character sequence", 12);
  std::string s6a(10, 'x');
  std::string s6b(10, 42); // 42 is the ASCII code for '*'
  std::string s7(s0.begin(), s0.begin() + 7);

  std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
  std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6a: " << s6a;
  std::cout << "\ns6b: " << s6b << "\ns7: " << s7 << '\n';
}

void StringTest::testErease() {
  std::string str("This is an example sentence.");
  std::cout << str << '\n';

  // "This is an example sentence."
  str.erase(10, 8); //            ^^^^^^^^
  std::cout << str << '\n';
  // "This is an sentence."
  str.erase(str.begin() + 9); //           ^

  std::cout << str << '\n';
  // "This is a sentence."
  str.erase(str.begin() + 5, str.end() - 9); //       ^^^^^
  std::cout << str << '\n';
  // "This sentence."
}

void StringTest::testShrink() {
  std::string str(100, 'x');
  std::cout << "1. capacity of str: " << str.capacity() << '\n';

  str.resize(10);
  std::cout << "2. capacity of str: " << str.capacity() << '\n';

  str.shrink_to_fit();
  std::cout << "3. capacity of str: " << str.capacity() << '\n';
}

void StringTest::testGetLine() {
  std::string name;

  std::cout << "Please, enter your full name: ";
  std::getline(std::cin, name);
  std::cout << "Hello, " << name << "!\n";
}

void StringTest::testFind() {
  std::string str("There are two needles in this haystack with needles.");
  std::string str2("needle");

  // different member versions of find in the same order as above:
  std::size_t found = str.find(str2);
  if (found != std::string::npos)
    std::cout << "first 'needle' found at: " << found << '\n';

  found = str.find("needles are small", found + 1, 6);
  if (found != std::string::npos)
    std::cout << "second 'needle' found at: " << found << '\n';

  found = str.find("haystack");
  if (found != std::string::npos)
    std::cout << "'haystack' also found at: " << found << '\n';

  found = str.find('.');
  if (found != std::string::npos)
    std::cout << "Period found at: " << found << '\n';

  // let's replace the first needle:
  str.replace(str.find(str2), str2.length(), "preposition");
  std::cout << str << '\n';
}

void StringTest::testData() {

  std::string str = "Test string";
  char cstr[] = "Test string";

  if (str.length() == std::strlen(cstr)) {
    std::cout << "str and cstr have the same length.\n";

    // str.data()  == str.c_str();

    if (memcmp(cstr, str.data(), str.length()) == 0)
      std::cout << "str and cstr have the same content.\n";
  }
}

void StringTest::testReplace() {
  std::string base = "this is a test string.";
  std::string str2 = "n example";
  std::string str3 = "sample phrase";
  std::string str4 = "useful.";

  // replace signatures used in the same order as described above:

  // Using positions:                 0123456789*123456789*12345
  std::string str = base;           // "this is a test string."
  str.replace(9, 5, str2);          // "this is an example string." (1)
  str.replace(19, 6, str3, 7, 6);   // "this is an example phrase." (2)
  str.replace(8, 10, "just a");     // "this is just a phrase."     (3)
  str.replace(8, 6, "a shorty", 7); // "this is a short phrase."    (4)
  str.replace(22, 1, 3, '!');       // "this is a short phrase!!!"  (5)

  // Using iterators: 0123456789*123456789*
  str.replace(str.begin(), str.end() - 3, str3); // "sample phrase!!!"      (1)
  str.replace(str.begin(), str.begin() + 6,
              "replace"); // "replace phrase!!!"     (3)
  str.replace(str.begin() + 8, str.begin() + 14, "is coolness",
              7); // "replace is cool!!!"    (4)
  str.replace(str.begin() + 12, str.end() - 4, 4,
              'o'); // "replace is cooool!!!"  (5)
  str.replace(str.begin() + 11, str.end(), str4.begin(),
              str4.end()); // "replace is useful."    (6)
  std::cout << str << '\n';
}

void testStrcpy() {
  char buf[10] = {0};
  memset(buf, sizeof(buf), 1);

  strcpy(buf, "12345");

  for (char c : buf) {
    if (isalpha(c)) {
      std::cout << " char:" << c << std::endl;
    } else {
      std::cout << "no char:" << (int)c << std::endl;
    }
  }
}

void testSubLen(char *str) {
  std::cout << strlen(str) << std::endl;
  std::cout << sizeof(str) << std::endl;
}

void testLen() {
  char str[100] = {0};

  for (int i = 0; i < 30; i++) {
    str[i] = 'a';
  }

  std::cout << strlen(str) << std::endl;
  std::cout << sizeof(str) << std::endl;

  testSubLen(str);
}

int main(int argc, char *argv[]) {
  StringTest test;

  // test.strtok();
  test.testAdd();
  // testLen();
}