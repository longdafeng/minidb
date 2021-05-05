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
#include "yacc_sql.tab.h"

selects *getSelects();
Condition *getCondition();
RelAttr *getRelAttr();
Value *getValue();
union sqls *getSqls();
sqlstr *getSqlstr();
RC parse(char *st, sqlstr *sqln);

int i;
// allocate struct of condition
Condition *getCondition() {
  Condition *condition;
  condition = (Condition *)malloc(sizeof(Condition));
  condition->lhsAttr = *getRelAttr();
  condition->rhsAttr = *getRelAttr();
  condition->lhsValue = *getValue();
  condition->rhsValue = *getValue();
  condition->bLhsIsAttr = -1;
  condition->bRhsIsAttr = -1;
  return condition;
}
// allocate struct of relattr
RelAttr *getRelAttr() {
  RelAttr *relAttr;
  relAttr = (RelAttr *)malloc(sizeof(RelAttr));
  relAttr->relName = (char *)malloc(sizeof(char) * MAX_REL_NAME);
  memset(relAttr->relName, 0, sizeof(char) * MAX_REL_NAME);
  relAttr->attrName = (char *)malloc(sizeof(char) * MAX_ATTR_NAME);
  memset(relAttr->attrName, 0, sizeof(char) * MAX_ATTR_NAME);
  return relAttr;
}
// allocate struct of value,the default type is int
Value *getValue() {
  Value *value = (Value *)malloc(sizeof(Value));
  value->data = (void *)malloc(sizeof(char) * MAX_DATA);
  memset(value->data, 0, sizeof(char) * MAX_DATA);
  value->type = ints;
  return value;
}
// allocate struct of select
selects *getSelects() {
  selects *se;
  se = (selects *)malloc(sizeof(selects));
  (se)->nSelAttrs = 0;
  for (i = 0; i < MAX_NUM; i++) {
    (se)->selAttrs[i] = getRelAttr();
  }
  (se)->nRelations = 0;
  for (i = 0; i < MAX_NUM; i++) {
    (se)->relations[i] = (char *)malloc(sizeof(char));
    memset(se->relations[i], 0, sizeof(char));
  }
  (se)->nConditions = 0;
  for (i = 0; i < MAX_NUM; i++) {
    (se)->conditions[i] = *getCondition();
  }
  return se;
}
// allocate union of sqls
union sqls *getSqls() {
  union sqls *sql;
  sql = (union sqls *)malloc(sizeof(union sqls));
  (sql)->sel = *getSelects();
  (sql)->errors = (char *)malloc(sizeof(char) * MAX_ERROR_MESSAGE);
  memset(sql->errors, 0, sizeof(char) * MAX_ERROR_MESSAGE);
  return sql;
}
sqlstr *getSqlstr() {
  sqlstr *sq;
  sq = (sqlstr *)malloc(sizeof(sqlstr));
  (sq)->flag = 0;
  (sq)->sstr = *getSqls();
  return sq;
}

extern int hust_parse(sqlstr *sqls);

RC parse(char *st, sqlstr *sqln) {

  yy_switch_to_buffer(yy_scan_string(st));

  if (sqln->flag == -1) {
    sqln->sstr = *getSqls();
  }

  hust_parse(sqln);
  if (sqln->flag == 0)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}