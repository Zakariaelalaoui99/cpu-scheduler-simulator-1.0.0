/**
 * \file sjf.cpp
 * \brief Auto-generated documentation header for sjf.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include "sjf.hpp"
#include <algorithm>

void SJF::execute(std::vector<Process>& processes,
                  std::vector<GanttEntry>& gantt,
                  int contextSwitch)
{
    gantt.clear();
    int n = (int)processes.size();
    if (n == 0) return;

    std::vector<bool> done(n,false);
    int time = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int best = 1e9;
        for (int i=0;i<n;++i) {
            if (done[i]) continue;
            if (processes[i].getArrivalTime() <= time) {
                if (processes[i].getBurstTime() < best) {
                    best = processes[i].getBurstTime();
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            int nextArrival = 1e9;
            for (int i=0;i<n;++i) if (!done[i])
                nextArrival = std::min(nextArrival, processes[i].getArrivalTime());
            time = std::max(time, nextArrival);
            continue;
        }
        auto& p = processes[idx];
        int start = time;
        int end = start + p.getBurstTime();
        gantt.push_back({p.getPid(), start, end, -1});
        p.setCompletionTime(end);
        p.setTurnaroundTime(end - p.getArrivalTime());
        p.setWaitingTime(p.getTurnaroundTime() - p.getBurstTime());
        done[idx] = true;
        ++completed;
        time = end + contextSwitch;
    }
}
