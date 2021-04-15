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

#ifndef CTESTSTRING_H_
#define CTESTSTRING_H_

/*
 *
 */
class StringTest {
public:
  StringTest();
  virtual ~StringTest();

  int strtok();

  int find();

  int testAdd();

  void testConstruct();

  void testErease();

  void testShrink();

  void testGetLine();

  void testFind();

  void testData();

  void testReplace();

private:
  const static char MESSAGE_SEP = ',';

  static int str_num;


};

#endif /* CTESTSTRING_H_ */
