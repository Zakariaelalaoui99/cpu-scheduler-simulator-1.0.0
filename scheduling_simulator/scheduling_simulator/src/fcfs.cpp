/**
 * \file fcfs.cpp
 * \brief Auto-generated documentation header for fcfs.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include "fcfs.hpp"

void FCFS::execute(std::vector<Process>& processes,
                   std::vector<GanttEntry>& gantt,
                   int contextSwitch)
{
    gantt.clear();
    if (processes.empty()) return;

    std::vector<int> idx(processes.size());
    for (size_t i=0;i<idx.size();++i) idx[i]=int(i);
    std::sort(idx.begin(), idx.end(), [&](int a, int b){
        if (processes[a].getArrivalTime() != processes[b].getArrivalTime())
            return processes[a].getArrivalTime() < processes[b].getArrivalTime();
        return processes[a].getPid() < processes[b].getPid();
    });

    int time = 0;
    for (int k=0;k<(int)idx.size();++k) {
        auto& p = processes[idx[k]];
        if (time < p.getArrivalTime()) time = p.getArrivalTime();
        int start = time;
        int end   = start + p.getBurstTime();
        gantt.push_back({p.getPid(), start, end, -1});
        p.setCompletionTime(end);
        p.setTurnaroundTime(end - p.getArrivalTime());
        p.setWaitingTime(p.getTurnaroundTime() - p.getBurstTime());
        time = end;
        if (k+1 < (int)idx.size()) time += contextSwitch;
    }
}
