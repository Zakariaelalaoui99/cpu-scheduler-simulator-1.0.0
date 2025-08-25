/**
 * \file ganttentry.hpp
 * \brief Auto-generated documentation header for ganttentry.hpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
/**
 * @struct GanttEntry
 * @brief One CPU interval assigned to a process (and optionally a thread).
 * @var GanttEntry::pid   Process identifier.
 * @var GanttEntry::start Inclusive start time.
 * @var GanttEntry::end   Exclusive end time.
 * @var GanttEntry::tid   Thread identifier or -1 when not applicable.
 */

struct GanttEntry {
    int pid{0};
    int start{0};
    int end{0};
    int tid{-1}; // -1 => process-only
};
