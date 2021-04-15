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


#include "log_test.h"


#include "gtest/gtest.h"

#include "common/log/log.h"


using namespace common;

LogTest::LogTest() {
  // TODO Auto-generated constructor stub
}

LogTest::~LogTest() {
  // TODO Auto-generated destructor stub
}

int LogTest::init(const std::string &logFile) {



  LoggerFactory::initDefault(logFile);

  gLog->SetRotateType(LOG_ROTATE_BYSIZE);

  return 0;
}

void *LogTest::log_loop(void *param) {
  int index = *(int *) param;
  int i = 0;
  while (i < 100) {
    i++;
    LOG_INFO("index:%d --> %d", index, i);
  }

  return NULL;
}

void checkRotate() {
  LogTest test;

  test.init();
  ASSERT_EQ(gLog->GetRotateType(), LOG_ROTATE_BYSIZE);

  int index = 30;
  test.log_loop(&index);
}

TEST(checkRotateTest, CheckRoateTest)
{

}

void testEnableTest() {
  LogTest test;

  test.init();


  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_PANIC, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_ERR, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_WARN, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_INFO, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_DEBUG, __FILE__), false);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_TRACE, __FILE__), false);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_LAST, __FILE__), false);

  gLog->SetDefaultModule(__FILE__);

  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_PANIC, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_ERR, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_WARN, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_INFO, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_DEBUG, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_TRACE, __FILE__), true);
  ASSERT_EQ(gLog->CheckOutput(LOG_LEVEL_LAST, __FILE__), true);
}

TEST(testEnableTest, CheckEnableTest)
{

}

int main(int argc, char **argv) {


  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果
  return RUN_ALL_TESTS();
}
