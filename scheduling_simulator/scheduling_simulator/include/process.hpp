/**
 * \file process.hpp
 * \brief Process entity used in the Scheduling Simulator.
 * \details A Process encapsulates scheduling input attributes
 *          (arrival time, burst length, priority), computed metrics
 *          (completion, turnaround, waiting time), and optional
 *          user-level threads.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include <vector>
#include "thread.hpp"

/**
 * @class Process
 * @brief Process entity with optional user-level threads.
 *
 * A Process is the fundamental schedulable unit in process-only mode.
 * When thread scheduling is enabled, threads can be attached to a Process:
 * - In kernel-level mode, threads are flattened to pseudo-processes.
 * - In user-level mode, threads are multiplexed inside the process slice.
 *
 * Each Process stores input attributes and computed metrics after scheduling.
 *
 * @see Thread
 * @see Scheduler::Mode
 */
class Process {
public:
    /**
     * @brief Construct a process with given attributes.
     * @param pid Unique process ID.
     * @param arrival Arrival time of the process.
     * @param burst CPU burst time (used in process-only mode).
     * @param prio Static scheduling priority (lower = higher priority).
     */
    explicit Process(int pid, int arrival = 0, int burst = 0, int prio = 0)
        : m_pid(pid), m_arrival(arrival), m_burst(burst), m_priority(prio) {}

    /** @name Identity */
    ///@{
    int  getPid() const { return m_pid; }
    /** @brief Set process identifier. */
    void setPid(int pid) { m_pid = pid; }
    ///@}

    /** @name Timing (process-level) */
    ///@{
    int  getArrivalTime() const { return m_arrival; }
    /** @brief Set arrival time. */
    void setArrivalTime(int t) { m_arrival = t; }

    int  getBurstTime() const { return m_burst; }
    /** @brief Set burst time. */
    void setBurstTime(int t) { m_burst = t; }

    int  getCompletionTime() const { return m_completion; }
    /** @brief Set completion time (time when process finishes). */
    void setCompletionTime(int t) { m_completion = t; }

    int  getTurnaroundTime() const { return m_turnaround; }
    /** @brief Set turnaround time = completion - arrival. */
    void setTurnaroundTime(int t) { m_turnaround = t; }

    int  getWaitingTime() const { return m_waiting; }
    /** @brief Set waiting time = turnaround - burst. */
    void setWaitingTime(int t) { m_waiting = t; }
    ///@}

    /** @name Priority */
    ///@{
    int  getPriority() const { return m_priority; }
    /** @brief Set scheduling priority. */
    void setPriority(int p) { m_priority = p; }
    ///@}

    /** @name Threads */
    ///@{
    /** @brief Attach a new thread to this process. */
    void addThread(const Thread& th) { m_threads.push_back(th); }
    /** @brief Get constant reference to threads. */
    const std::vector<Thread>& getThreads() const { return m_threads; }
    /** @brief Get mutable reference to threads. */
    std::vector<Thread>& threadsRef() { return m_threads; }

    /** @brief Sum of all thread burst times. */
    int totalThreadBurst() const {
        int s = 0;
        for (const auto& t : m_threads) s += t.getBurstTime();
        return s;
    }
    ///@}

private:
    int m_pid{0};           ///< Process identifier.
    int m_arrival{0};       ///< Arrival time.
    int m_burst{0};         ///< CPU burst (when no threads are present).
    int m_completion{0};    ///< Completion time (set after scheduling).
    int m_turnaround{0};    ///< Turnaround time (completion - arrival).
    int m_waiting{0};       ///< Waiting time (turnaround - burst).
    int m_priority{0};      ///< Static scheduling priority.
    std::vector<Thread> m_threads; ///< Threads owned by this process.
};
