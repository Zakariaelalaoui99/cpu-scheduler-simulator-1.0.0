/**
 * \file rr.hpp
 * \brief Round-Robin scheduling algorithm.
 * \details Provides a preemptive Round-Robin scheduler with fixed time quantum.
 *          Processes are scheduled in a cyclic order, each receiving up to
 *          `quantum` time units per turn. If a process still has remaining
 *          burst time after its slice, it is placed at the back of the ready queue.
 *          Context switch overhead can be modeled via the `contextSwitch` parameter.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include "schedulingalgorithm.hpp"

/**
 * @class RR
 * @brief Round-Robin scheduler with fixed quantum (preemptive).
 *
 * The Round-Robin scheduler maintains a FIFO ready queue of processes.
 * Each process that arrives is enqueued in arrival order, then scheduled
 * in cyclic fashion:
 * - Runs for at most `quantum` time units.
 * - If the process still has remaining burst time after its slice, it is
 *   re-enqueued at the back of the ready queue.
 * - If completed, its completion/turnaround/waiting metrics are finalized.
 *
 * This scheduler ensures fairness by time-slicing the CPU among all ready processes.
 *
 * @see SchedulingAlgorithm
 */
class RR : public SchedulingAlgorithm {
public:
    /**
     * @brief Construct a Round-Robin scheduler with a given quantum.
     * @param q Time slice (quantum) in time units.
     */
    explicit RR(int q) : quantum(q) {}

    /**
     * @brief Execute Round-Robin scheduling on a list of processes.
     * @param processes In/out list of processes to be scheduled. Metrics
     *        such as completion, turnaround, and waiting times will be updated.
     * @param gantt Output sequence of Gantt chart entries showing which
     *        process ran at what times.
     * @param contextSwitch Context switch cost (time units) applied between
     *        consecutive slices when switching processes.
     */
    void execute(std::vector<Process>& processes,
                 std::vector<GanttEntry>& gantt,
                 int contextSwitch = 0) override;

    /**
     * @brief Get the human-readable name of this algorithm.
     * @return String "RR".
     */
    QString getName() const override { return "RR"; }

private:
    int quantum{1}; ///< Fixed quantum (time slice) in time units.
};
