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

#include "common/seda/seda_metric.h"
#include "common/seda/seda_config.h"
namespace common {

std::vector<std::string> SedaQueueInfo::stage_names;

SedaQueueInfo::SedaQueueInfo() { update(); }

SedaQueueInfo::SedaQueueInfo(const SedaQueueInfo &rhs) {
  this->queue_info = rhs.queue_info;
}

SedaQueueInfo &SedaQueueInfo::operator=(const SedaQueueInfo &rhs) {
  if (this != &rhs)
    this->queue_info = rhs.queue_info;
  return *this;
}

void SedaQueueInfo::update() {
  SedaConfig::getInstance()->getStageQueueStatus(queue_info);
}

void SedaQueueInfo::dump(std::ostream &os) const {
  if (queue_info.empty())
    return;

  if (stage_names.empty()) {
    SedaConfig::getInstance()->getStageNames(stage_names);
    ASSERT(stage_names.size() == queue_info.size(),
           "stage number and queue number don't match");
  }

  size_t i = 0;
  for (; i < queue_info.size(); ++i)
    os << stage_names[i] << "=" << queue_info[i] << "\t";
  os << "\n";

  return;
}

} //namespace common