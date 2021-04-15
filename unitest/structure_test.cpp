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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/defs.h"
#include "structure_test.h"

using namespace common;

StructureTest::StructureTest() {
  // TODO Auto-generated constructor stub
}

StructureTest::~StructureTest() {
  // TODO Auto-generated destructor stub
}

const static int BLOCKID_LEN = 128;

typedef struct _blockGeography {
  u64_t mOffset;
  u64_t mLen;
  u64_t mStatus;
  char mBlockId[BLOCKID_LEN];
} BlockGeography;

typedef struct _dataGeography {
  u32_t mVersion;
  u32_t mHardLinkNum;
  u32_t mBlockNum;
  BlockGeography mBlocks[0];
} DataGeography;

typedef struct _dataGeographyStore {
  u32_t mVersion;
  int test;
  union {
    char mValue[ONE_KILO];
    DataGeography mDataGeography;
  };
} DataGeographyStore;

/**
 * 结构体默认的字节对齐一般满足三个准则：
 * 1) 结构体变量的首地址能够被其最宽基本类型成员的大小所整除；
 * 2)
 * 结构体每个成员相对于结构体首地址的偏移量（offset）都是成员自身大小的整数倍，
 *    如有需要编译器会在成员之间加上填充字节（internal adding）；
 * 3) 结构体的总大小为结构体最宽基本类型成员大小的整数倍，
 *    如有需要编译器会在最末一个成员之后加上填充字节（trailing padding）。
 */

/**
 * #pragma pack(1)// 设置1字节对齐
 *  __attribute((aligned (n)))，让所作用的结构成员对齐在n字节自然边界上。
 *            如果结构中有成员的长度大于n，则按照最大成员的长度来对齐。
 *  __attribute__ ((packed))，取消结构在编译过程中的优化对齐，
 *            按照实际占用字节数进行对齐。
 */
int StructureTest::pos() {
  // int blockNum = 0;
  size_t offset = ((size_t) & ((DataGeography *)0)->mBlocks);

  std::cout << offset << std::endl;
  std::cout << sizeof(DataGeography) << std::endl;

  DataGeography *pData = (DataGeography *)malloc(sizeof(DataGeography) +
                                                 10 * sizeof(BlockGeography));

  pData->mBlockNum = 10;

  for (int i = 0; i < 10; i++) {
    BlockGeography *pBg = &pData->mBlocks[i];
    printf("i :%d:%p  offset:%d\n", i, pBg, (int)((char *)pBg - (char *)pData));
  }

  free(pData);

  return 0;
}

typedef struct _Dy {
  void Cleanup();
  const int len;
  char buf[0];
} Dy;

void Dy::Cleanup() { memset(buf, 0, len); }

void StructureTest::funcNoMem() {
  int *dy = (int *)malloc(sizeof(Dy) + 100);
  if (dy == NULL) {
    return;
  }
  *dy = 100;

  Dy *dy1 = (Dy *)dy;
  dy1->Cleanup();
  std::cout << dy1->len << std::endl;

  free(dy);
}

enum {
  HDR_NUM_PRECISION = 7,
  HDR_TYPE_LEN = 8,
  HDR_MSG_LEN = HDR_NUM_PRECISION + 1,
  HDR_ATT_LEN = HDR_NUM_PRECISION + 1,
  HDR_FILE_LEN = HDR_NUM_PRECISION + 1,
  HDR_LEN = HDR_TYPE_LEN + HDR_MSG_LEN + HDR_ATT_LEN + HDR_FILE_LEN,
  HDR_TYPE_POS = 0,
  HDR_MSG_LEN_POS = HDR_TYPE_POS + HDR_TYPE_LEN,
  HDR_ATT_LEN_POS = HDR_MSG_LEN_POS + HDR_MSG_LEN,
  HDR_FILE_LEN_POS = HDR_ATT_LEN_POS + HDR_ATT_LEN
};

typedef struct _packHeader {
  _packHeader() { memset(this, 0, sizeof(*this)); }

  char mType[HDR_TYPE_LEN];
  char mMsgLen[HDR_MSG_LEN];
  char mAttLen[HDR_ATT_LEN];
  char mFileLen[HDR_FILE_LEN];
  void setHeader(const char *hdrType, const char *msgLen, const char *attLen,
                 const char *fileLen) {

    memset(this, 0, sizeof(struct _packHeader));

    strncpy(mType, hdrType, HDR_TYPE_LEN - 1);
    strncpy(mMsgLen, msgLen, HDR_NUM_PRECISION);
    strncpy(mAttLen, attLen, HDR_NUM_PRECISION);
    strncpy(mFileLen, attLen, HDR_NUM_PRECISION);
  }
} PackHeader __attribute__((aligned(1)));

void StructureTest::testStructInit() {
  PackHeader *a = new PackHeader();
  char *p = (char *)a;
  for (unsigned int i = 0; i < sizeof(PackHeader); i++) {
    printf("%d ", p[i]);
    if (i % HDR_TYPE_LEN == 0) {
      printf("\n");
    }
  }
}

void StructureTest::testStub() {
  pos();

  funcNoMem();

  testStructInit();
}

void testStruct() {
  StructureTest *testStructure = new StructureTest();
  testStructure->testStub();
}

int main(int argc, char **argv) { return 0; }