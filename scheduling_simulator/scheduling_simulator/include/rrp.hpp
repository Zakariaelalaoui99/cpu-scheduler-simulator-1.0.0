/**
 * \file rrp.hpp
 * \brief Priority Round-Robin scheduling algorithm.
 * \details Provides a preemptive Priority Round-Robin scheduler with fixed time quantum.
 *          Processes are first grouped by static priority. Higher-priority processes
 *          are always scheduled before lower-priority ones. Within the same priority
 *          group, Round-Robin with a fixed quantum is applied to ensure fairness.
 *          Context switch overhead can be modeled via the `contextSwitch` parameter.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include "schedulingalgorithm.hpp"

/**
 * @class RRP
 * @brief Priority Round-Robin scheduler.
 *
 * The Priority Round-Robin scheduler combines priority scheduling with
 * Round-Robin time-slicing:
 * - Processes are placed into ready queues based on their static priority.
 * - At each decision point, the scheduler always selects from the highest
 *   priority queue that is non-empty.
 * - Within a priority level, Round-Robin is applied: each process receives
 *   up to `quantum` time units before being re-queued if it still has
 *   remaining burst time.
 *
 * This approach balances responsiveness (via priorities) with fairness
 * (via Round-Robin inside each priority level).
 *
 * @see SchedulingAlgorithm
 */
class RRP : public SchedulingAlgorithm {
public:
    /**
     * @brief Construct a Priority Round-Robin scheduler with a given quantum.
     * @param q Time slice (quantum) in time units applied within each priority level.
     */
    explicit RRP(int q) : quantum(q) {}

    /**
     * @brief Execute Priority Round-Robin scheduling on a list of processes.
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
     * @return String "RRP".
     */
    QString getName() const override { return "RRP"; }

private:
    int quantum{1}; ///< Time slice (quantum) applied within each priority queue.
};

