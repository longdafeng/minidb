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

#ifndef CTESTTHREAD_H_
#define CTESTTHREAD_H_

#include "common/lang/mutex.h"

/*
 *
 */
class ThreadTest {
public:
  ThreadTest();
  virtual ~ThreadTest();

  int create();

  int startTestCond();
  int startTestDeadLock();

  static void *testCond(void *param);
  static void *testDeadLock(void *param);

private:
  int param[10];

  pthread_mutex_t mutex;
  pthread_cond_t cond;

  pthread_mutex_t dead_mutex1;
  pthread_mutex_t dead_mutex2;
};

#endif /* CTESTTHREAD_H_ */
