/**
 * \file controller.hpp
 * \brief Qt Controller for the Scheduling Simulator.
 * \details Connects the MainWindow UI with the simulation core (Scheduler).
 *          Handles user actions, configures the Scheduler, runs simulations,
 *          and updates the MainWindow with results.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include <QObject>
#include "scheduler.hpp"

class MainWindow;

/**
 * @class Controller
 * @brief Mediator between the Qt GUI (MainWindow) and the simulation engine (Scheduler).
 *
 * The Controller listens to signals from the MainWindow, applies changes to
 * the Scheduler (adding processes, changing algorithm, switching mode, etc.),
 * and triggers execution. After execution, it calls back into the MainWindow
 * to display results (process list, computed metrics, and Gantt chart).
 *
 * Responsibilities:
 * - Handle process creation and inject it into the Scheduler.
 * - Switch scheduling algorithms (FCFS, SJF, RR, RRP) as selected in the UI.
 * - Run simulations on demand and forward results to the MainWindow.
 * - Apply context switch time, mode selection, and thread quantum from UI controls.
 *
 * @see MainWindow
 * @see Scheduler
 */
class Controller : public QObject {
    Q_OBJECT
public:
    Controller(Scheduler* scheduler, MainWindow* mainWindow);

public slots:
    void handleProcessCreation(const Process& p);
    void handleAlgorithmSelection(const QString& name, int quantum);
    void handleExecution();
    void handleClearProcesses();
    void handleContextSwitchChanged(int cs);
    void handleModeSelected(const QString& name);
    void handleThreadQuantumChanged(int q);

private:
    Scheduler* m_scheduler{nullptr};   ///< Simulation engine instance.
    MainWindow* m_mainWindow{nullptr}; ///< Owning GUI for input/output.
};
