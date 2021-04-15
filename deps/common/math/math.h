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

#ifndef __COMMON_MATH_MATH_H__
#define __COMMON_MATH_MATH_H__
namespace common {

/**
 * give seed for random number generation
 * TODO: the implementation of rand() in glibc is thread-safe,
 *       but it will take a global lock to protect static data structure.
 *       could consider using XrandNN_r() later
 */
void seedRandom();

/**
 * if scope is bigger than RAND_MAX/10, the precision is not good
 */
long int lrandom(const long int scope);

} //namespace common
#endif /* __COMMON_MATH_MATH_H__ */
