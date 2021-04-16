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

#ifndef __COMMON_OS_PIDFILE_H__
#define __COMMON_OS_PIDFILE_H__
namespace common {


//! Generates a PID file for the current component
/**
 * Gets the process ID (PID) of the calling process and writes a file
 * dervied from the input argument containing that value in a system
 * standard directory, e.g. /var/run/progName.pid
 *
 * @param[in] programName as basis for file to write
 * @return    0 for success, error otherwise
 */
int writePidFile(const char *progName);

//! Cleanup PID file for the current component
/**
 * Removes the PID file for the current component
 *
 */
void removePidFile(void);

std::string& getPidPath();

} //namespace common
#endif // __COMMON_OS_PIDFILE_H__
