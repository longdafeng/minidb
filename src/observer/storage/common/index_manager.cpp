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
#include "storage/common/index_manager.h"
#include "rc.h"

RC createIndex(const char *fileName, AttrType attrType, int attrLength) {

  //TODO
  return RC::SUCCESS;
}

RC openIndex(const char *fileName, IndexHandle *indexHandle) {
  //TODO
  return RC::SUCCESS;
}

RC closeIndex(IndexHandle *indexHandle) {
  //TODO
  return RC::SUCCESS;
}

RC insertEntry(IndexHandle *indexHandle, void *data, const RID *rid) {
  //TODO
  return RC::SUCCESS;
}

RC deleteEntry(IndexHandle *indexHandle, void *data, const RID *rid) {
  //TODO
  return RC::SUCCESS;
}

RC openIndexScan(IndexScan *indexScan, IndexHandle *indexHandle,
                 CompOp compOp, char *value) {
  //TODO
  return RC::SUCCESS;
}

RC getNextIndexEntry(IndexScan *indexScan, RID *rid) {
  //TODO
  return RC::SUCCESS;
}

RC closeIndexScan(IndexScan *indexScan) {
  //TODO
  return RC::SUCCESS;
}

RC getIndexTree(char *fileName, Tree *index) {
  //TODO
  return RC::SUCCESS;
}
