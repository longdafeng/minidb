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
#ifndef __OBSERVER_STORAGE_COMMON_INDEX_MANAGER_H_
#define __OBSERVER_STORAGE_COMMON_INDEX_MANAGER_H_

#include "index_manager.h"
#include "record_manager.h"

typedef struct {
  int attrLength;
  int keyLength;
  AttrType attrType;
  PageNum rootPage;
  PageNum first_leaf;
  int order;
} IndexFileHeader;

typedef struct {
  bool open;
  BPFileHandle fileHandle;
  IndexFileHeader fileHeader;
} IndexHandle;

typedef struct {
  int is_leaf;
  int keynum;
  PageNum parent;
  PageNum brother;
  char *keys;
  RID *rids;
} IndexNode;

typedef struct {
  bool open;
  IndexHandle *pIXIndexHandle;
  CompOp compOp;
  char *value;
  BPPageHandle pfPageHandles[BP_BUFFER_SIZE];
  PageNum pnNext;
} IndexScan;

typedef struct TreeNode {
  int keyNum;
  char **keys;
  TreeNode *parent;
  TreeNode *sibling;
  TreeNode *firstChild;
} TreeNode;

typedef struct {
  AttrType attrType;
  int attrLength;
  int order;
  TreeNode *root;
} Tree;

/**
 * 此函数创建一个名为fileName的索引。
 * attrType描述被索引属性的类型，attrLength描述被索引属性的长度
 * @param fileName
 * @param attrType
 * @param attrLength
 * @return
 */
RC createIndex(const char *fileName, AttrType attrType, int attrLength);

/**
 * 打开名为fileName的索引文件。
 * 如果方法调用成功，则indexHandle为指向被打开的索引句柄的指针。
 * 索引句柄用于在索引中插入或删除索引项，也可用于索引的扫描
 * @param fileName
 * @param indexHandle
 * @return
 */
RC openIndex(const char *fileName, IndexHandle *indexHandle);

/**
 * 关闭句柄indexHandle对应的索引文件
 * @param indexHandle
 * @return
 */
RC closeIndex(IndexHandle *indexHandle);

/**
 * 此函数向IndexHandle对应的索引中插入一个索引项。
 * 参数pData指向要插入的属性值，参数rid标识该索引项对应的元组，
 * 即向索引中插入一个值为（*pData，rid）的键值对
 * @param indexHandle
 * @param data
 * @param rid
 * @return
 */
RC insertEntry(IndexHandle *indexHandle, void *data, const RID *rid);

/**
 * 从IndexHandle句柄对应的索引中删除一个值为（*pData，rid）的索引项
 * @param indexHandle
 * @param data
 * @param rid
 * @return
 */
RC deleteEntry(IndexHandle *indexHandle, void *data, const RID *rid);

/**
 * 用于在indexHandle对应的索引上初始化一个基于条件的扫描。
 * compOp和*value指定比较符和比较值，indexScan为初始化后的索引扫描结构指针
 * @param indexScan
 * @param indexHandle
 * @param compOp
 * @param value
 * @return
 */
RC openIndexScan(IndexScan *indexScan, IndexHandle *indexHandle,
                 CompOp compOp, char *value);

/**
 * 用于继续IndexScan句柄对应的索引扫描，获得下一个满足条件的索引项，
 * 并返回该索引项对应的记录的ID
 * @param indexScan
 * @param rid
 * @return
 */
RC getNextIndexEntry(IndexScan *indexScan, RID *rid);

/**
 * 关闭一个索引扫描，释放相应的资源
 * @param indexScan
 * @return
 */
RC closeIndexScan(IndexScan *indexScan);

/**
 * 获取由fileName指定的B+树索引内容，返回指向B+树的指针。
 * 此函数提供给测试程序调用，用于检查B+树索引内容的正确性
 * @param fileName
 * @param index
 * @return
 */
RC getIndexTree(char *fileName, Tree *index);

#endif //__OBSERVER_STORAGE_COMMON_INDEX_MANAGER_H_