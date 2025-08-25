/**
 * \file scheduler.cpp
 * \brief Auto-generated documentation header for scheduler.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include "scheduler.hpp"
#include <algorithm>

void Scheduler::removeProcess(int pid) {
    m_processes.erase(std::remove_if(m_processes.begin(), m_processes.end(),
        [&](const Process& p){ return p.getPid()==pid; }), m_processes.end());
}

bool Scheduler::addThreadToProcess(int pid, const Thread& th) {
    auto it = std::find_if(m_processes.begin(), m_processes.end(),
        [&](const Process& p){ return p.getPid()==pid; });
    if (it == m_processes.end()) return false;
    it->threadsRef().push_back(th);
    return true;
}

void Scheduler::execute() {
    switch (m_mode) {
        case Mode::ProcessOnly: executeProcessOnly(); break;
        case Mode::ThreadKernel: executeThreadKernel(); break;
        case Mode::ThreadUser: executeThreadUser(); break;
    }
}

void Scheduler::executeProcessOnly() {
    m_gantt.clear();
    if (m_algorithm) {
        m_algorithm->execute(m_processes, m_gantt, m_contextSwitch);
    }
}

int Scheduler::sumRemaining(const std::vector<Thread>& ts) {
    int s=0; for (auto& t:ts) s += t.getRemaining(); return s;
}
int Scheduler::firstArrival(const std::vector<Thread>& ts) {
    int a=1e9; for (auto& t:ts) a = std::min(a, t.getArrivalTime()); return a==1e9?0:a;
}

void Scheduler::executeThreadKernel() {
    // Flatten to pseudo-processes per thread
    struct Back { int pid; int tid; };
    std::vector<Process> flat;
    std::vector<Back> back;
    for (const auto& p : m_processes) {
        for (const auto& t : p.getThreads()) {
            int tmpPid = p.getPid()*100000 + t.getTid();
            Process fp(tmpPid, p.getArrivalTime()+t.getArrivalTime(), t.getBurstTime(), t.getPriority());
            flat.push_back(fp);
            back.push_back({p.getPid(), t.getTid()});
        }
    }
    std::vector<GanttEntry> gflat;
    if (m_algorithm) m_algorithm->execute(flat, gflat, m_contextSwitch);

    // Map back
    m_gantt.clear();
    for (const auto& ge : gflat) {
        auto it = std::find_if(flat.begin(), flat.end(),
            [&](const Process& x){return x.getPid()==ge.pid;});
        if (it==flat.end()) continue;
        size_t k = size_t(it - flat.begin());
        m_gantt.push_back({back[k].pid, ge.start, ge.end, back[k].tid});
    }

    // Propagate results to processes/threads
    for (auto& p : m_processes) {
        int procEnd = 0;
        int sumBurst = 0;
        for (auto& t : p.threadsRef()) {
            int tmpPid = p.getPid()*100000 + t.getTid();
            auto it = std::find_if(flat.begin(), flat.end(),
                [&](const Process& x){return x.getPid()==tmpPid;});
            if (it==flat.end()) continue;
            t.setCompletionTime(it->getCompletionTime());
            t.setTurnaroundTime(t.getCompletionTime() - (p.getArrivalTime()+t.getArrivalTime()));
            t.setWaitingTime(t.getTurnaroundTime() - t.getBurstTime());
            procEnd = std::max(procEnd, t.getCompletionTime());
            sumBurst += t.getBurstTime();
        }
        p.setCompletionTime(procEnd);
        p.setTurnaroundTime(procEnd - p.getArrivalTime());
        p.setWaitingTime(p.getTurnaroundTime() - sumBurst);
    }
}

void Scheduler::executeThreadUser() {
    // 1) Schedule processes by total burst of their threads
    std::vector<Process> outer = m_processes;
    for (auto& p : outer) p.setBurstTime(p.totalThreadBurst());
    std::vector<GanttEntry> outerG;
    if (m_algorithm) m_algorithm->execute(outer, outerG, m_contextSwitch);

    // 2) For each outer slice, time-slice threads of that process by RR(q)
    m_gantt.clear();
    for (const auto& seg : outerG) {
        auto pit = std::find_if(m_processes.begin(), m_processes.end(),
            [&](const Process& P){return P.getPid()==seg.pid;});
        if (pit==m_processes.end()) continue;

        // copy threads to track remaining
        std::vector<Thread> th = pit->getThreads();
        const int n = (int)th.size();
        if (n==0) continue;
        std::vector<int> rem(n), arrival(n);
        for (int i=0;i<n;++i) {
            rem[i] = th[i].getBurstTime();
            arrival[i] = pit->getArrivalTime() + th[i].getArrivalTime();
        }

        int t = seg.start;
        const int end = seg.end;
        const int q = std::max(1, m_threadQuantum);


        // build simple cyclic order by tid
        std::vector<int> order(n);
        for (int i=0;i<n;++i) order[i]=i;
        int cur = 0;

        while (t < end) {
            // find next ready thread with remaining > 0
            bool found = false;
            for (int tries=0; tries<n; ++tries) {
                int i = order[cur];
                cur = (cur+1)%n;
                if (rem[i] <= 0) continue;
                if (arrival[i] > t) continue;
                const int slice = std::min(q, rem[i]);
                int sliceEnd = std::min(end, t + slice);
                if (sliceEnd>t) {
                    m_gantt.push_back({seg.pid, t, sliceEnd, th[i].getTid()});
                    rem[i] -= (sliceEnd - t);
                    t = sliceEnd;
                    found = true;
                    break;
                }
            }
            if (!found) {
                // jump to earliest arrival still pending or to end
                int na = end;
                for (int i=0;i<n;++i) if (rem[i]>0) na = std::min(na, arrival[i]);
                if (na <= t) na = t+1;
                t = std::min(end, na);
            }
        }

        // set thread completion times as last end seen
        for (int i=0;i<n;++i) {
            int lastEnd = 0;
            for (const auto& ge : m_gantt) if (ge.pid==seg.pid && ge.tid==th[i].getTid())
                lastEnd = std::max(lastEnd, ge.end);
            th[i].setCompletionTime(lastEnd);
            th[i].setTurnaroundTime(lastEnd - (pit->getArrivalTime()+th[i].getArrivalTime()));
            th[i].setWaitingTime(th[i].getTurnaroundTime() - th[i].getBurstTime());
        }
        // update process metrics
        int procEnd = 0, sumBurst = 0;
        for (auto& tth : th) { procEnd = std::max(procEnd, tth.getCompletionTime()); sumBurst += tth.getBurstTime(); }
        pit->setCompletionTime(procEnd);
        pit->setTurnaroundTime(procEnd - pit->getArrivalTime());
        pit->setWaitingTime(pit->getTurnaroundTime() - sumBurst);
    }
}
