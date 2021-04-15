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

#ifndef CTESTFILE_H_
#define CTESTFILE_H_

/*
 *
 */
class FileTest {
public:
  FileTest();
  virtual ~FileTest();

  int openfile();

  void open_lseek();

  int fstream();

  int readdir(int argc, char **argv);

  int ifstream();

  int ofstream();

  void ofstream_loop();

  void binlog();

  void fopen();
};

#endif /* CTESTFILE_H_ */
