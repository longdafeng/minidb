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
#include "storage/common/record_manager.h"
#include "handler/handler.h"

RC openScan(RecordFileScan *rmFileScan, RecordFileHandle *fileHandle, int conNum,
            Con *conditions)
{
  //TODO
  return RC::SUCCESS;
}

RC closeScan(RecordFileScan *rmFileScan) {
  //TODO
  return RC::SUCCESS;
}

RC getNextRec(RecordFileScan *rmFileScan, Record *rec) {
  //TODO
  return RC::SUCCESS;
}

RC getRec(RecordFileHandle *fileHandle, RID *rid, Record *rec) {
  //TODO
  return RC::SUCCESS;
}

RC insertRec(RecordFileHandle *fileHandle, char *data, RID *rid) {
  //TODO
  return RC::SUCCESS;
}

RC deleteRec(RecordFileHandle *fileHandle, const RID *rid) {
  //TODO
  return RC::SUCCESS;
}

RC updateRec(RecordFileHandle *fileHandle, const Record *rec) {
  //TODO
  return RC::SUCCESS;
}

RC RecordCreateFile(char *fileName, int recordSize) {
  //TODO
  return RC::SUCCESS;
}

RC RecordOpenFile(char *fileName, RecordFileHandle *fileHandle) {
  //TODO
  return RC::SUCCESS;
}

RC RecordCloseFile(RecordFileHandle *fileHandle) {
  //TODO
  return RC::SUCCESS;
}