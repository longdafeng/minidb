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

#ifndef __COMMON_MM_DEBUG_NEW_H__
#define __COMMON_MM_DEBUG_NEW_H__

#include <new>
#include <stdlib.h>
namespace common {

/* Prototypes */
bool check_leaks();
void *operator new(size_t size, const char *file, int line);
void *operator new[](size_t size, const char *file, int line);
#ifndef NO_PLACEMENT_DELETE
void operator delete(void *pointer, const char *file, int line);
void operator delete[](void *pointer, const char *file, int line);
#endif // NO_PLACEMENT_DELETE
void operator delete[](void *); // MSVC 6 requires this declaration

/* Macros */
#ifndef DEBUG_NEW_NO_NEW_REDEFINITION
#define new DEBUG_NEW
#define DEBUG_NEW new (__FILE__, __LINE__)
#define debug_new new
#else
#define debug_new new (__FILE__, __LINE__)
#endif // DEBUG_NEW_NO_NEW_REDEFINITION
#ifdef DEBUG_NEW_EMULATE_MALLOC

#define malloc(s) ((void *)(debug_new char[s]))
#define free(p) delete[](char *)(p)
#endif // DEBUG_NEW_EMULATE_MALLOC

/* Control flags */
extern bool new_verbose_flag;   // default to false: no verbose information
extern bool new_autocheck_flag; // default to true: call check_leaks() on exit

} //namespace common
#endif // __COMMON_MM_DEBUG_NEW_H__
