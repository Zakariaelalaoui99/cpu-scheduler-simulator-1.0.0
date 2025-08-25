/**
 * \file rrp.cpp
 * \brief Auto-generated documentation header for rrp.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include "rrp.hpp"
#include <vector>
#include <queue>
#include <algorithm>

void RRP::execute(std::vector<Process>& processes,
                  std::vector<GanttEntry>& gantt,
                  int contextSwitch)
{
    struct Node{int idx; int pr; long long order;};
    auto cmp = [](const Node&a, const Node&b){
        if (a.pr!=b.pr) return a.pr > b.pr; // lower number = higher priority
        return a.order > b.order;
    };
    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> pq(cmp);

    gantt.clear();
    const int n = (int)processes.size();
    if (n==0) return;
    std::vector<int> remaining(n);
    for (int i=0;i<n;++i) remaining[i] = processes[i].getBurstTime();

    std::vector<int> idx(n);
    for (int i=0;i<n;++i) idx[i]=i;
    std::sort(idx.begin(), idx.end(), [&](int a, int b){
        if (processes[a].getArrivalTime()!=processes[b].getArrivalTime())
            return processes[a].getArrivalTime() < processes[b].getArrivalTime();
        return processes[a].getPid() < processes[b].getPid();
    });

    int time = processes[idx[0]].getArrivalTime();
    int nextIdx = 0;
    long long ord = 0;

    auto pushArrivals = [&](int t){
        while (nextIdx < n && processes[idx[nextIdx]].getArrivalTime() <= t) {
            pq.push({idx[nextIdx], processes[idx[nextIdx]].getPriority(), ord++});
            ++nextIdx;
        }
    };
    pushArrivals(time);

    int completed = 0;
    while (completed < n) {
        if (pq.empty()) {
            if (nextIdx < n) {
                time = std::max(time, processes[idx[nextIdx]].getArrivalTime());
                pushArrivals(time);
            } else break;
            continue;
        }
        auto node = pq.top(); pq.pop();
        int i = node.idx;
        int slice = std::min(quantum, remaining[i]);
        int start = time;
        int end = start + slice;
        gantt.push_back({processes[i].getPid(), start, end, -1});
        remaining[i]-=slice;
        time = end;
        if (remaining[i]==0) {
            processes[i].setCompletionTime(time);
            processes[i].setTurnaroundTime(time - processes[i].getArrivalTime());
            processes[i].setWaitingTime(processes[i].getTurnaroundTime() - processes[i].getBurstTime());
            ++completed;
        } else {
            pq.push({i, processes[i].getPriority(), ord++});
        }
        if (!pq.empty()) time += contextSwitch;
        pushArrivals(time);
    }
}
