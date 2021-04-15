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

#ifndef __COMMON_LANG_SERIALIZABLE_H__
#define __COMMON_LANG_SERIALIZABLE_H__

#include <string>
namespace common {

/**
 * Through this type to determine object type
 */
enum {
  MESSAGE_BASIC = 100,
  MESSAGE_BASIC_REQUEST = 1000,
  MESSAGE_BASIC_RESPONSE = -1000
};

class Deserializable {
public:
  /*
   * deserialize buffer to one object
   * @param[in]buffer,     buffer to store the object serialized bytes
   * @return *             object
   */
  virtual void *deserialize(const char *buffer, int bufLen) = 0;
};

class Serializable {
public:
  /*
   * serialize this object to bytes
   * @param[in] buffer,    buffer to store the object serialized bytes,
   *                       please make sure the buffer is enough
   * @param[in] bufferLen, buffer length
   * @return,              used buffer length -- success, -1 means failed
   */
  virtual int serialize(char *buffer, int bufferLen) = 0;

  /*
   * deserialize bytes to this object
   * @param[in] buffer      buffer to store the object serialized bytes
   * @param[in] bufferLen   buffer lenght
   * @return                used buffer length -- success , -1 --failed
   */
  virtual int deserialize(const char *buffer, int bufferLen) = 0;

  /**
   * get serialize size
   * @return                >0 -- success, -1 --failed
   */
  virtual int getSerialSize() = 0;

  /**
   * this function will generalize one output string
   */
  virtual void toString(std::string &output) = 0;
};

} //namespace common
#endif /* __COMMON_LANG_SERIALIZABLE_H__ */
