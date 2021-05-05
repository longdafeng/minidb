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
#ifndef __OBSERVER_STORAGE_COMMON_RECORD_MANAGER_H_
#define __OBSERVER_STORAGE_COMMON_RECORD_MANAGER_H_

#include "handler/handler.h"
#include "storage/default/disk_buffer_pool.h"

typedef int SlotNum;

typedef struct {
  PageNum pageNum; // record's page number
  SlotNum slotNum; // record's slot number
  bool valid;      // true means a valid record
} RID;

typedef struct {
  bool valid; // false means the recard hasn't been load
  RID rid;    // record's rid
  char *data; // record's data
} Record;

typedef struct {
  int bLhsIsAttr, bRhsIsAttr; //左、右是属性（1）还是值（0）
  AttrType attrType;
  int LattrLength, RattrLength;
  int LattrOffset, RattrOffset;
  CompOp compOp;
  void *Lvalue, *Rvalue;
} Con;

class RecordFileHandle {
public:
  RecordFileHandle() {
    open = false;
    // TODO: 添加需要初始话代码
  }

private:
  bool open; //句柄是否打开（是否正在被使用）
  // TODO: 需要自定义其内部结构
};

class RecordFileScan {
public:
  RecordFileScan() {
    open = false;
    pRMFileHandle = NULL;
    conditions = NULL;
  }

public:
  bool open;                       //扫描是否打开
  RecordFileHandle *pRMFileHandle; //扫描的记录文件句柄
  int conNum;                      //扫描涉及的条件数量
  Con *conditions;                 //扫描涉及的条件数组指针
  BPPageHandle PageHandle;         //处理中的页面句柄
  PageNum pn;                      //扫描即将处理的页面号
  SlotNum sn;                      //扫描即将处理的插槽号
};

/**
 * 创建一个名为fileName的记录文件，该文件中每条记录的大小为recordSize
 * @param fileName
 * @param recordSize
 * @return
 */
RC RecordCreateFile(char *fileName, int recordSize);

/**
 * 根据文件名打开指定的记录文件，返回其文件句柄指针
 * @param fileName
 * @param fileHandle
 * @return
 */
RC RecordOpenFile(char *fileName, RecordFileHandle *fileHandle);

/**
 * 关闭给定句柄对应的记录文件
 * @param fileHandle
 * @return
 */
RC RecordCloseFile(RecordFileHandle *fileHandle);

/**
 * 打开一个文件扫描。
 * 本函数利用从第二个参数开始的所有输入参数初始化一个由参数rmFileScan指向的文件扫描结构，
 * 在使用中，用户应先调用此函数初始化文件扫描结构，
 * 然后再调用GetNextRec函数来逐个返回文件中满足条件的记录。
 * 如果条件数量conNum为0，则意味着检索文件中的所有记录。
 * 如果条件不为空，则要对每条记录进行条件比较，只有满足所有条件的记录才被返回
 * @param rmFileScan
 * @param fileHandle
 * @param conNum
 * @param conditions
 * @return
 */
RC openScan(RecordFileScan *rmFileScan, RecordFileHandle *fileHandle,
            int conNum, Con *conditions);

/**
 * 关闭一个文件扫描，释放相应的资源
 * @param rmFileScan
 * @return
 */
RC closeScan(RecordFileScan *rmFileScan);

/**
 * 获取一个符合扫描条件的记录。
 * 如果该方法成功，返回值rec应包含记录副本及记录标识符。
 * 如果没有发现满足扫描条件的记录，则返回RM_EOF
 * @param rmFileScan
 * @param rec
 * @return
 */
RC getNextRec(RecordFileScan *rmFileScan, Record *rec);

/**
 * 更新指定文件中的记录，rec指向的记录结构中的rid字段为要更新的记录的标识符，
 * pData字段指向新的记录内容
 * @param fileHandle
 * @param rec
 * @return
 */
RC updateRec(RecordFileHandle *fileHandle, const Record *rec);

/**
 * 从指定文件中删除标识符为rid的记录
 * @param fileHandle
 * @param rid
 * @return
 */
RC deleteRec(RecordFileHandle *fileHandle, const RID *rid);

/**
 * 插入一个新的记录到指定文件中，pData为指向新纪录内容的指针，返回该记录的标识符rid
 * @param fileHandle
 * @param data
 * @param rid
 * @return
 */
RC insertRec(RecordFileHandle *fileHandle, char *data, RID *rid);

/**
 * 获取指定文件中标识符为rid的记录内容到rec指向的记录结构中
 * @param fileHandle
 * @param rid
 * @param rec
 * @return
 */
RC getRec(RecordFileHandle *fileHandle, RID *rid, Record *rec);


#endif //__OBSERVER_STORAGE_COMMON_RECORD_MANAGER_H_