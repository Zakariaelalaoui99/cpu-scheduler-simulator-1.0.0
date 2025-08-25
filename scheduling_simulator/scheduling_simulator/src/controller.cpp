/**
 * \file controller.cpp
 * \brief Auto-generated documentation header for controller.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include "controller.hpp"
#include "mainwindow.hpp"
#include "fcfs.hpp"
#include "sjf.hpp"
#include "rr.hpp"
#include "rrp.hpp"

Controller::Controller(Scheduler* scheduler, MainWindow* mainWindow)
    : m_scheduler(scheduler), m_mainWindow(mainWindow)
{}

void Controller::handleProcessCreation(const Process& p) {
    if (!m_scheduler) return;
    m_scheduler->addProcess(p);
    m_mainWindow->showProcesses(m_scheduler->getResults());
}

void Controller::handleAlgorithmSelection(const QString& name, int quantum) {
    if (!m_scheduler) return;
    if (name == "FCFS") m_scheduler->setAlgorithm(std::make_unique<FCFS>());
    else if (name == "SJF") m_scheduler->setAlgorithm(std::make_unique<SJF>());
    else if (name == "RR") m_scheduler->setAlgorithm(std::make_unique<RR>(quantum));
    else if (name == "RRP") m_scheduler->setAlgorithm(std::make_unique<RRP>(quantum));
}

void Controller::handleExecution() {
    if (!m_scheduler) return;
    m_scheduler->execute();
    m_mainWindow->displayResult(m_scheduler->getResults());
    m_mainWindow->displayGantt(m_scheduler->getGantt());
}

void Controller::handleClearProcesses() {
    if (!m_scheduler) return;
    m_scheduler->clear();
    m_mainWindow->showProcesses({});
    m_mainWindow->displayGantt({});
    m_mainWindow->displayResult({});
}

void Controller::handleContextSwitchChanged(int cs) {
    if (!m_scheduler) return;
    m_scheduler->setContextSwitch(cs);
}

void Controller::handleModeSelected(const QString& name) {
    if (!m_scheduler) return;
    if (name.contains("Process")) m_scheduler->setMode(Scheduler::Mode::ProcessOnly);
    else if (name.contains("Kernel")) m_scheduler->setMode(Scheduler::Mode::ThreadKernel);
    else m_scheduler->setMode(Scheduler::Mode::ThreadUser);
}

void Controller::handleThreadQuantumChanged(int q) {
    if (!m_scheduler) return;
    m_scheduler->setThreadQuantum(q);
}
