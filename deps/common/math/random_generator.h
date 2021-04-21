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
// Created by Longda on 2021/4/20.
//
#ifndef __COMMON_MATH_RANDOM_GENERATOR_H_
#define __COMMON_MATH_RANDOM_GENERATOR_H_

#include <stdlib.h>
#include <random>
namespace common
{

#define DEFAULT_RANDOM_BUFF_SIZE 512

class RandomGenerator
{

public:
    RandomGenerator();
    virtual ~RandomGenerator();

public:
    unsigned int next();
    unsigned int next(unsigned int range);

private:
     // The GUN Extended TLS Version
     std::mt19937 randomData;
};

}

#endif /* __COMMON_MATH_RANDOM_GENERATOR_H_ */
