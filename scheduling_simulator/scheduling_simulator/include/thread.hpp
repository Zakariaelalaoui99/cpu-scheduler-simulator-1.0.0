/**
 * \file thread.hpp
 * \brief Thread entity for the Scheduling Simulator.
 * \details Represents a schedulable thread owned by a Process. Threads carry
 *          arrival and burst times relative to their process and can be
 *          scheduled either as kernel-visible entities or multiplexed
 *          within process quanta in user-level mode. Computed metrics
 *          (completion, turnaround, waiting) are populated after simulation.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include <string>

/**
 * @class Thread
 * @brief Schedulable thread owned by a Process.
 *
 * Each Thread encapsulates scheduling parameters such as arrival time,
 * burst duration, and priority. Depending on the Scheduler mode:
 * - In **ThreadKernel** mode, threads are treated as independent
 *   schedulable units, flattened into pseudo-processes.
 * - In **ThreadUser** mode, threads are multiplexed in user space
 *   within the time slice allocated to their parent process.
 *
 * Threads also track results (completion, turnaround, waiting time)
 * after scheduling is complete.
 *
 * @see Process
 * @see Scheduler::Mode
 */
class Thread {
public:
    /**
     * @brief Construct a Thread with given attributes.
     * @param id Unique thread identifier (relative to its process).
     * @param arrival Relative arrival time (added to process arrival).
     * @param burst CPU burst time required.
     * @param prio Static scheduling priority (lower = higher priority).
     */
    explicit Thread(int id, int arrival = 0, int burst = 0, int prio = 0)
        : m_tid(id), m_arrival(arrival), m_burst(burst),
        m_remaining(burst), m_priority(prio) {}

    /** @name Identity */
    ///@{
    int  getTid() const { return m_tid; }
    /** @brief Set thread identifier. */
    void setTid(int id) { m_tid = id; }
    ///@}

    /** @name Timing */
    ///@{
    int  getArrivalTime() const { return m_arrival; }
    /** @brief Set relative arrival time. */
    void setArrivalTime(int t) { m_arrival = t; }

    int  getBurstTime() const { return m_burst; }
    /** @brief Set burst time (resets remaining time as well). */
    void setBurstTime(int t) { m_burst = t; m_remaining = t; }

    int  getRemaining() const { return m_remaining; }
    /** @brief Update remaining execution time (for preemptive schedulers). */
    void setRemaining(int r) { m_remaining = r; }
    ///@}

    /** @name Results (set after scheduling) */
    ///@{
    int  getCompletionTime() const { return m_completion; }
    /** @brief Set completion time (when the thread finished). */
    void setCompletionTime(int t) { m_completion = t; }

    int  getTurnaroundTime() const { return m_turnaround; }
    /** @brief Set turnaround time = completion - (process arrival + thread arrival). */
    void setTurnaroundTime(int t) { m_turnaround = t; }

    int  getWaitingTime() const { return m_waiting; }
    /** @brief Set waiting time = turnaround - burst. */
    void setWaitingTime(int t) { m_waiting = t; }
    ///@}

    /** @name Scheduling parameters */
    ///@{
    int  getPriority() const { return m_priority; }
    /** @brief Set static priority of the thread. */
    void setPriority(int p) { m_priority = p; }
    ///@}

    /** @name State (for UI) */
    ///@{
    const std::string& getState() const { return m_state; }
    /** @brief Set UI-visible state string (e.g., "Running", "Waiting"). */
    void setState(std::string s) { m_state = std::move(s); }
    ///@}

private:
    int m_tid{0};         ///< Thread identifier.
    int m_arrival{0};     ///< Relative arrival time.
    int m_burst{0};       ///< CPU burst length.
    int m_remaining{0};   ///< Remaining burst time (mutable in RR/priority RR).
    int m_completion{0};  ///< Completion time.
    int m_turnaround{0};  ///< Turnaround time.
    int m_waiting{0};     ///< Waiting time.
    int m_priority{0};    ///< Static priority.
    std::string m_state;  ///< Optional descriptive state for UI display.
};
