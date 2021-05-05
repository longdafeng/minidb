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

#include "executor.h"


const RC query(char *sql, SelResult *res) { return RC::SUCCESS; }

const RC select(int nSelAttrs, RelAttr **selAttrs, int nRelations, char **relations,
          int nConditions, Condition *conditions, SelResult *res) {
  return RC::SUCCESS;
}
