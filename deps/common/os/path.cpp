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
// Created by Longda on 2010
//
#include <string.h>

#include "common/defs.h"
#include "common/os/path.h"
namespace common {

std::string getFileName(const std::string &fullPath) {
  std::string szRt;
  size_t pos;
  try {
    pos = fullPath.rfind(FILE_PATH_SPLIT);
    if (pos != std::string::npos && pos < fullPath.size() - 1) {
      szRt = fullPath.substr(pos + 1, fullPath.size() - pos - 1);
    } else if (pos == std::string::npos) {
      szRt = fullPath;
    } else {
      szRt = "";
    }

  } catch (...) {
  }
  return szRt;
}

void getFileName(const char *path, std::string &fileName) {
  // Don't care the last character as FILE_PATH_SPLIT
  const char *endPos = strrchr(path, FILE_PATH_SPLIT);
  if (endPos == NULL) {
    fileName = path;
    return;
  }

  if (strcmp(path, FILE_PATH_SPLIT_STR) == 0) {
    fileName.assign("");
  } else {
    fileName.assign(endPos + 1);
  }

  return;
}

std::string getDirName(const std::string &fullPath) {
  std::string szRt;
  size_t pos;
  try {
    pos = fullPath.rfind(FILE_PATH_SPLIT);
    if (pos != std::string::npos && pos > 0) {
      szRt = fullPath.substr(0, pos);
    } else if (pos == std::string::npos) {
      szRt = fullPath;
    } else {
      // pos == 0
      szRt = FILE_PATH_SPLIT_STR;
    }

  } catch (...) {
  }
  return szRt;
}
void getDirName(const char *path, std::string &parent) {
  // Don't care the last character as FILE_PATH_SPLIT
  const char *endPos = strrchr(path, FILE_PATH_SPLIT);
  if (endPos == NULL) {
    parent = path;
    return;
  }

  if (endPos == path) {
    parent.assign(path, 1);
  } else {
    parent.assign(path, endPos - path);
  }

  return;
}

std::string getFilePath(const std::string &fullPath) {
  std::string szRt;
  size_t pos;
  try {
    pos = fullPath.rfind("/");
    if (pos != std::string::npos) {
      szRt = fullPath.substr(0, pos);
    } else if (pos == std::string::npos) {
      szRt = fullPath;
    } else {
      szRt = "";
    }

  } catch (...) {
  }
  return szRt;
}

std::string getAboslutPath(const char *path) {
  std::string aPath(path);
  if (path[0] != '/') {
    const int MAX_SIZE = 256;
    char current_absolute_path[MAX_SIZE];

    if (NULL == getcwd(current_absolute_path, MAX_SIZE)) {
    }
  }

  return aPath;
}

} //namespace common