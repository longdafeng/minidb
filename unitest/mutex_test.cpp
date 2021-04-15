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
#include <pthread.h>
#include <unistd.h>

#define DEBUG_LOCK
#include "common/lang/mutex.h"

#define THREAD_NUM 2

using namespace common;

typedef struct MutexContex {
  int num;
  int maxNum;
  pthread_mutex_t mutex;
} MutexContex_t;

void *runDeadLock(void *ctx) {
  LOG_INFO("Starting to run for thread !");

  MutexContex_t *mutexCtx = (MutexContex_t *)ctx;

  MUTEX_LOCK(&mutexCtx->mutex);

  // wait other thread to start
  sleep(10);
  MutexContex_t *targetMutexCtx = NULL;
  if (mutexCtx->num + 1 < mutexCtx->maxNum) {
    targetMutexCtx = mutexCtx + 1;
  } else {
    targetMutexCtx = mutexCtx - (mutexCtx->maxNum - 1);
  }

  LOG_INFO("Starting to lock target in %d!", mutexCtx->num);
  MUTEX_LOCK(&targetMutexCtx->mutex);
  LOG_INFO("Successfully lock target in %d!", mutexCtx->num);
  MUTEX_UNLOCK(&targetMutexCtx->mutex);

  MUTEX_UNLOCK(&mutexCtx->mutex);
  LOG_INFO("Starting to exit!");

  return NULL;
}

void testDeadlockCheck() {
  LoggerFactory::initDefault("testmutex.log");

  for (int i = 0; i < 4; i++) {

    pthread_mutexattr_t mutexatr;
    pthread_mutexattr_init(&mutexatr);
    pthread_mutexattr_settype(&mutexatr, i);

    MutexContex_t *mutexsContext =
        (MutexContex_t *)malloc(sizeof(MutexContex_t) * THREAD_NUM);
    if (mutexsContext == NULL) {
      continue;
    }

    for (int j = 0; j < THREAD_NUM; j++) {
      MutexContex_t *mutexCtx = mutexsContext + j;
      mutexCtx->num = j;
      mutexCtx->maxNum = THREAD_NUM;
      MUTEX_INIT(&(mutexCtx->mutex), &mutexatr);

      pthread_t pThread;
      pthread_create(&pThread, NULL, runDeadLock, (void *)mutexCtx);
    }

    sleep(100);

    // if occur deadlock, destroy mutex will crash
    // for (int j = 0; j < THREAD_NUM; j++)
    // {
    //     MUTEX_DESTROY(&((mutexsContext+ j)->mutex));
    // }

    // delete mutexsContext;
  }
}

void testLockTwice() {
  pthread_mutexattr_t mutexatr;
  pthread_mutexattr_init(&mutexatr);
  pthread_mutexattr_settype(&mutexatr, PTHREAD_MUTEX_RECURSIVE);

  pthread_mutex_t mutex;

  pthread_mutex_init(&mutex, &mutexatr);

  std::cout << "Lock first time " << &mutex << std::endl;
  pthread_mutex_lock(&mutex);

  std::cout << "Lock twice " << &mutex << std::endl;
  pthread_mutex_lock(&mutex);

  std::cout << "Unlock first time " << &mutex << std::endl;
  pthread_mutex_unlock(&mutex);
  std::cout << "Unlock second time " << &mutex << std::endl;
  pthread_mutex_unlock(&mutex);
}

void testDeadLockTwice() {
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  std::cout << "Lock first time " << &mutex << std::endl;
  pthread_mutex_lock(&mutex);

  std::cout << "Lock twice time " << &mutex << std::endl;
  pthread_mutex_lock(&mutex);

  std::cout << "Unlock first time " << &mutex << std::endl;
  pthread_mutex_unlock(&mutex);
  std::cout << "Unlock second time " << &mutex << std::endl;
  pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv) {
  // testLockTwice();
  // testDeadlockCheck();
  return 0;
}