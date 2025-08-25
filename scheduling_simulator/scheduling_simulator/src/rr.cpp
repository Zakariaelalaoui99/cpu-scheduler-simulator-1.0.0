/**
 * \file rr.cpp
 * \brief Auto-generated documentation header for rr.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include "rr.hpp"
#include <queue>
#include <algorithm>

void RR::execute(std::vector<Process>& processes,
                 std::vector<GanttEntry>& gantt,
                 int contextSwitch)
{
    gantt.clear();
    if (processes.empty()) return;

    const int n = (int)processes.size();
    std::vector<int> remaining(n);
    for (int i=0;i<n;++i) remaining[i] = processes[i].getBurstTime();

    std::vector<int> idx(n);
    for (int i=0;i<n;++i) idx[i]=i;
    std::sort(idx.begin(), idx.end(), [&](int a, int b){
        if (processes[a].getArrivalTime()!=processes[b].getArrivalTime())
            return processes[a].getArrivalTime() < processes[b].getArrivalTime();
        return processes[a].getPid() < processes[b].getPid();
    });

    std::queue<int> q;
    int time = 0;
    int nextIdx = 0;
    int completed = 0;

    auto pushArrivals = [&](int t){
        while (nextIdx < n && processes[idx[nextIdx]].getArrivalTime() <= t) {
            q.push(idx[nextIdx]);
            ++nextIdx;
        }
    };

    if (n>0) time = processes[idx[0]].getArrivalTime();
    pushArrivals(time);

    while (completed < n) {
        if (q.empty()) {
            if (nextIdx < n) {
                time = std::max(time, processes[idx[nextIdx]].getArrivalTime());
                pushArrivals(time);
                continue;
            } else break;
        }
        int i = q.front(); q.pop();
        pushArrivals(time);

        int slice = std::min(quantum, remaining[i]);
        int start = time;
        int end   = start + slice;
        gantt.push_back({processes[i].getPid(), start, end, -1});
        remaining[i] -= slice;
        time = end;

        if (remaining[i] == 0) {
            processes[i].setCompletionTime(time);
            processes[i].setTurnaroundTime(time - processes[i].getArrivalTime());
            processes[i].setWaitingTime(processes[i].getTurnaroundTime() - processes[i].getBurstTime());
            ++completed;
        } else {
            q.push(i);
        }
        if (!q.empty()) time += contextSwitch;
        pushArrivals(time);
    }
}
