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

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <time.h>

// struct timeval
//{
//    long tv_sec; /*秒*/
//    long tv_usec; /*微秒*/
//};
// struct tm
//{
//    int tm_sec; /*秒，正常范围0-59， 但允许至61*/
//    int tm_min; /*分钟，0-59*/
//    int tm_hour; /*小时， 0-23*/
//    int tm_mday; /*日，即一个月中的第几天，1-31*/
//    int tm_mon; /*月， 从一月算起，0-11*/
//    int tm_year; /*年， 从1900至今已经多少年*/
//    int tm_wday; /*星期，一周中的第几天， 从星期日算起，0-6*/
//    int tm_yday; /*从今年1月1日到目前的天数，范围0-365*/
//    int tm_isdst; /*日光节约时间的旗标*/
//};

// char *asctime(const struct tm* timeptr);
//将结构中的信息转换为真实世界的时间，以字符串的形式显示
// char *ctime(const time_t *timep);
//将timep转换为真是世界的时间，以字符串显示，它和asctime不同就在于传入的参数形式不一样
// double difftime(time_t time1, time_t time2);
//返回两个时间相差的秒数
// int gettimeofday(struct timeval *tv, struct timezone *tz);
//返回当前距离1970年的秒数和微妙数，后面的tz是时区，一般不用
// struct tm* gmtime(const time_t *timep);
//将time_t表示的时间转换为没有经过时区转换的UTC时间，是一个struct tm结构指针
// stuct tm* localtime(const time_t *timep);
//和gmtime类似，但是它是经过时区转换的时间。
// time_t mktime(struct tm* timeptr);
//将struct tm 结构的时间转换为从1970年至今的秒数
//        time_t time(time_t *t);

int getSecond(void) {
  time_t t = time(0);
  char tmp[64];
  strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A 本年第%j天 %z", localtime(&t));
  std::cout << tmp << std::endl;
  return 0;
}

int main(int argc, char **argv) { return 0; }