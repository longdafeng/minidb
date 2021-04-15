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

#ifndef __COMMON_MATH_MD5_H__
#define __COMMON_MATH_MD5_H__
#include <stdio.h>
namespace common {

typedef unsigned char *POINTER;
typedef unsigned short int UINT2;
typedef unsigned int UINT4;

typedef struct {
  UINT4 state[4];           /* state (ABCD) */
  UINT4 count[2];           /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64]; /* input buffer */
} MD5_CTX;

#ifdef __cplusplus
extern "C" {
#endif

/** md5 for string
 *  parameters:
 *           string: the string to md5
 *           digest: store the md5 digest
 *  return: 0 for success, != 0 fail
 */
int MD5String(char *string, unsigned char digest[16]);

/** md5 for file
 *  parameters:
 *           filename: the filename whose content to md5
 *           digest: store the md5 digest
 *  return: 0 for success, != 0 fail
 */
int MD5File(char *filename, unsigned char digest[16]);

/** md5 for buffer
 *  parameters:
 *           buffer: the buffer to md5
 *           len: the buffer length
 *           digest: store the md5 digest
 *  return: 0 for success, != 0 fail
 */
int MD5Buffer(char *buffer, unsigned int len, unsigned char digest[16]);

void MD5Init(MD5_CTX *);

void MD5Update(MD5_CTX *, unsigned char *, unsigned int);

void MD5Final(unsigned char[16], MD5_CTX *);

#ifdef __cplusplus
}
#endif

} //namespace common
#endif //__COMMON_MATH_MD5_H__
