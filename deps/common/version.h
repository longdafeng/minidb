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

#ifndef __COMMON_VERSION_H__
#define __COMMON_VERSION_H__
namespace common {

#ifndef MAIJOR_VER
#define MAIJOR_VER 1
#endif

#ifndef MINOR_VER
#define MINOR_VER 0
#endif

#ifndef PATCH_VER
#define PATCH_VER 0
#endif

#ifndef OTHER_VER
#define OTHER_VER 1
#endif

#define STR1(R) #R
#define STR2(R) STR1(R)

#define VERSION_STR                                                            \
  (STR2(MAIJOR_VER) "." STR2(MINOR_VER) "." STR2(PATCH_VER) "." STR2(OTHER_VER))
#define VERSION_NUM                                                            \
  (MAIJOR_VER << 24 | MINOR_VER << 16 | PATCH_VER << 8 | OTHER_VER)

} //namespace common
#endif //__COMMON_VERSION_H__
