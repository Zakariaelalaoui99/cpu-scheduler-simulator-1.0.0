/**
 * \file fcfs.hpp
 * \brief Auto-generated documentation header for fcfs.hpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include "schedulingalgorithm.hpp"
#include <algorithm>/**
 * @class FCFS
 * @brief First-Come, First-Served (non-preemptive) scheduler.
 *
 * Runs processes in non-decreasing arrival time; ties broken by PID for
 * determinism. Each selected process runs to completion.
 */



class FCFS : public SchedulingAlgorithm {
public:
    void execute(std::vector<Process>& processes,
                 std::vector<GanttEntry>& gantt,
                 int contextSwitch = 0) override;
    QString getName() const override { return "FCFS"; }
};
