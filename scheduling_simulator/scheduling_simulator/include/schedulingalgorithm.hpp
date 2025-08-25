/**
 * \file schedulingalgorithm.hpp
 * \brief Auto-generated documentation header for schedulingalgorithm.hpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include <vector>
#include <QString>
#include "process.hpp"
#include "ganttentry.hpp"/**
 * @class SchedulingAlgorithm
 * @brief Interface for pluggable CPU scheduling algorithms.
 *
 * A SchedulingAlgorithm receives a snapshot of processes (arrival, burst,
 * priority) and produces an ordered list of Gantt segments describing when
 * each process runs on the single CPU. Implementations should not mutate
 * process identity; they may fill computed metrics (e.g., completion time).
 */



class SchedulingAlgorithm {
public:
    virtual ~SchedulingAlgorithm() = default;
/**
 * @brief Run the algorithm and build a Gantt chart.
 * @param processes In/out processes to schedule; implementations may update
 *        metrics like completion/turnaround times.
 * @param gantt Output sequence of [start,end) CPU segments (PID and optional TID).
 * @param contextSwitch Context switch cost (time units) inserted between slices
 *        when the next segment switches to a different PID.
 */
    virtual void execute(std::vector<Process>& processes,
                         std::vector<GanttEntry>& gantt,
                         int contextSwitch = 0) = 0;
    virtual QString getName() const = 0;
};
