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
// Created by Longda on 2021/3/27.
//

#ifndef __COMMON_OS_PATH_H__
#define __COMMON_OS_PATH_H__

#include <string>
namespace common {


/**
 * get file name from full path
 * example
 * input: /test/happy/  --> return : ""
 * input: /test/happy   --> return : happy
 * input: test/happy    --> return : happy
 * input: happy         --> return : happy
 * input: ""            --> return : ""
 */
std::string getFileName(const std::string &fullPath);
void getFileName(const char *path, std::string &fileName);

/**
 * get file path from full path
 * example
 * input: /test/happy   --> return : /test
 * input: test/happy    --> return : test
 * input: happy         --> return : happy
 * input: ""            --> return : ""
 */
std::string getFilePath(const std::string &fullPath);
void getDirName(const char *path, std::string &parent);

/**
 *  Get absolute path
 * input: path
 * reutrn absolutely path
 */
std::string getAboslutPath(const char *path);

} //namespace common
#endif //__COMMON_OS_PATH_H__
