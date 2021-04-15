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

// Include Files

#include <ctime>
#include <sys/time.h>

#include "common/seda/seda_stats.h"
#include "common/seda/seda_stats_event.h"
#include "common/seda/seda_stats_stage.h"
#include "common/seda/stage.h"
#include "common/seda/stage_event.h"
namespace common {

// Constructor
SedaStats::SedaStats(sedaStatsCategory_t category,
                     sedaStatsIdentifier_t identifier, bool persistent)
  : _category(category), _statId(identifier), _isCounter(false),
    _statCount(0), _resetCount(false), _persistent(persistent) {
  _enabled = SedaStatsStage::isCategoryEnabled(category) || persistent;

  // If enabled then collect the stats
  if (_enabled)
    gettimeofday(&_startTime, NULL);
}

SedaStats::SedaStats(sedaStatsCategory_t category, const std::string &strId,
                     bool persistent)
  : _category(category), _statId(strId), _isCounter(false), _statCount(0),
    _resetCount(false), _persistent(persistent) {
  _enabled = SedaStatsStage::isCategoryEnabled(category) || persistent;
  // If enabled then collect the stats
  if (_enabled)
    gettimeofday(&_startTime, NULL);
}

// Increment count
void SedaStats::incCount() {
  _isCounter = true;
  ++_statCount;
}

// Decrement count
void SedaStats::decCount() {
  _isCounter = true;
  --_statCount;
}

// Set the count
void SedaStats::setCount(int count) {
  _isCounter = true;
  _statCount = count;
}

// Reset count
void SedaStats::resetCount(int count) {
  _statCount = count;
  _resetCount = true;
  _isCounter = true;
}

void SedaStats::recordCount(sedaStatsCategory_t category,
                            const StatsId &statsId, int count,
                            bool persistent) {
  if (SedaStatsStage::isCategoryEnabled(category) || persistent) {
    SedaStatsEvent *e = new SedaStatsEvent(category, statsId, persistent);
    e->setStatCount(count);
    SedaStatsStage::addStatsEvent(e);
    e = NULL;
  }

  return;
}

// Destructor
SedaStats::~SedaStats() {
  _enabled &= (SedaStatsStage::isCategoryEnabled(_category) || _persistent);
  // stats is enabled
  if (true == _enabled) {
    // Record end time
    gettimeofday(&_endTime, NULL);

    // send time difference to statsCollectStage
    unsigned long long result =
      (_endTime.tv_sec - _startTime.tv_sec) * 1000000 + _endTime.tv_usec -
        _startTime.tv_usec;

    SedaStatsEvent *sedaStatsEv =
      new SedaStatsEvent(_category, _statId, _persistent);
    sedaStatsEv->setTime(result);

    if (true == _isCounter || true == _resetCount)
      sedaStatsEv->setStatCount(_statCount);
    sedaStatsEv->resetCount(_resetCount);

    SedaStatsStage::addStatsEvent(sedaStatsEv);
  }
}

} //namespace common