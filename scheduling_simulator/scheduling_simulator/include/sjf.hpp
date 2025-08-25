/**
 * \file sjf.hpp
 * \brief Auto-generated documentation header for sjf.hpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include "schedulingalgorithm.hpp"/**
 * @class SJF
 * @brief Shortest Job First (non-preemptive) scheduler.
 *
 * Among arrived jobs, selects the minimum burst time and runs it to completion.
 * (Preemptive SRTF can be added as a separate algorithm if desired.)
 */



class SJF : public SchedulingAlgorithm {
public:
    void execute(std::vector<Process>& processes,
                 std::vector<GanttEntry>& gantt,
                 int contextSwitch = 0) override;
    QString getName() const override { return "SJF"; }
};
