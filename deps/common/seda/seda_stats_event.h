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
#ifndef __COMMON_SEDA_SEDA_STATS_EVENT_H__
#define __COMMON_SEDA_SEDA_STATS_EVENT_H__

#include "common/seda/seda_stats.h"
#include "common/seda/stage_event.h"
namespace common {


class SedaStatsEvent : public StageEvent {
public:
  /// @brief Constructor
  ///
  /// @param[in] identifier   identify the stat being collected
  /// @param[in] time         time taken for stat
  SedaStatsEvent(SedaStats::sedaStatsCategory_t category,
                 const SedaStats::StatsId &statId, bool persistent);

  //! @brief Return category of the stat being recorded
  SedaStats::sedaStatsCategory_t getCategory() const;

  /// @brief Return the ID for the stat being recorded
  const SedaStats::StatsId &getStatID() const;

  /// @brief Return if time is collected in this event
  bool hasTime() const;

  /// @brief Return if a count was collected in this event
  bool hasCount() const;

  /// @brief Return the time stored in the event
  unsigned long long getTime() const;

  /// @brief Set stat time
  void setTime(unsigned long long);

  /// @brief Return the count set in the event
  ///
  /// @return count
  int getStatCount() const;

  // Set stat count
  void setStatCount(int count);

  // @brief Set 'ResetCounter' flag
  void resetCount(bool flag);

  // @brief Return 'ResetCounter' flag
  bool resetCount() const;

  // is persistent
  bool isPersistent() const;

private:
  SedaStats::sedaStatsCategory_t _category; /**< \brief Category of event */
  SedaStats::StatsId _statId;   /**< \brief ID for the stat recorded */
  unsigned long long _statTime; /**< \brief Time to be recorded */
  int _statCount;               /**< \brief Count for stat */
  bool _timeCollected;  /**< \brief Was time collected as part of stat */
  bool _countCollected; /**< \brief Was a count collected as part of stat */
  bool _resetCount;
  bool _persistent; /**< \brief The stats is persistent over clear commands */
};

} //namespace common
#endif //__COMMON_SEDA_SEDA_STATS_EVENT_H__
