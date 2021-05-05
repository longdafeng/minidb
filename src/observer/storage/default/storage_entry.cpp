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
// Created by Longda on 2021/4/13.
//


#include "handler/handler.h"
#include "sql/executor/executor.h"
#include "storage/common/record_manager.h"
#include "storage/common/index_manager.h"

RC execute(char *sql) {
  return RC::GENERIC_ERROR;
  /*
          sqlstr *sql_str = NULL;
          RC rc;
          sql_str = getSqlstr();
          rc = parse(sql, sql_str);//只有两种返回结果SUCCESS和SQL_SYNTAX

          if (rc == SUCCESS) {
                  switch (sql_str->flag) {
                          //case 1:
                          //判断SQL语句为select语句
                          //break;

                          case 2:
                          //判断SQL语句为insert语句
                          break;

                          case 3:
                          //判断SQL语句为update语句
                          break;

                          case 4:
                          //判断SQL语句为delete语句
                          break;

                          case 5:
                          //判断SQL语句为createTable语句
                          break;

                          case 6:
                          //判断SQL语句为dropTable语句
                          break;

                          case 7:
                          //判断SQL语句为createIndex语句
                          break;

                          case 8:
                          //判断SQL语句为dropIndex语句
                          break;

                          case 9:
                          //判断为help语句，可以给出帮助提示
                          break;

                          case 10:
                          //判断为exit语句，可以由此进行退出操作
                          break;
          }
          else {
                  //fprintf(stderr, "SQL Errors: %s", sql_str->sstr.errors);
                  return rc;
          }
  */
}

RC createDB(char *dbpath, char *dbname) {
  // TODO
  return RC::GENERIC_ERROR; }

RC dropDB(char *dbname) {
  //TODO
  return RC::GENERIC_ERROR;
}

RC openDB(char *dbname) {
  // TODO
  return RC::GENERIC_ERROR;
}

RC closeDB() {
  //TODO
  return RC::GENERIC_ERROR;
}

RC createTable(char *relName, int attrCount, AttrInfo *attributes) {
  //TODO
  return RC::GENERIC_ERROR;
}

RC dropTable(char *relName) {
  //TODO
  return RC::GENERIC_ERROR; }

RC IndexExist(char *relName, char *attrName, Record *rec) {
  //TODO
  return RC::GENERIC_ERROR;
}

RC createIndex(char *indexName, char *relName, char *attrName) {
  //TODO
  return RC::GENERIC_ERROR;
}

RC dropIndex(char *indexName) {
  //TODO
  return RC::GENERIC_ERROR;
}

RC insertRecord(char *relName, int nValues, Value *values) {
  //TODO
  return RC::GENERIC_ERROR;
}

RC deleteRecord(char *relName, int nConditions, Condition *conditions) {
  //TODO
  return RC::GENERIC_ERROR;
}

RC update(char *relName, char *attrName, Value *value, int nConditions,
          Condition *conditions) {
  //TODO
  return RC::GENERIC_ERROR;
}
