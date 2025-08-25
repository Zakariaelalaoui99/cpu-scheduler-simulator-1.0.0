/**
 * \file mainwindow.hpp
 * \brief Qt main window for the Scheduling Simulator.
 * \details Provides the top-level GUI where users create processes/threads,
 *          select the scheduling algorithm and mode, configure parameters
 *          (context switch time, quantum), run simulations, and visualize results.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include <QMainWindow>
#include <vector>
#include "process.hpp"
#include "ganttentry.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Top-level Qt window for the Scheduling Simulator.
 *
 * Provides the graphical user interface for creating processes/threads,
 * selecting scheduling algorithms (FCFS, SJF, RR, RRP), choosing the execution
 * mode (process-only, kernel-level threads, user-level threads), and configuring
 * simulation parameters such as context switch time and quantum.
 *
 * Interaction model:
 * - Emits signals (e.g., @c processCreated, @c algorithmSelected, @c runRequested)
 *   based on user actions.
 * - The Controller listens to these signals, runs the Scheduler, and returns
 *   results.
 * - Slots such as @c showProcesses, @c displayResult, and @c displayGantt update
 *   tables and the Gantt chart view.
 *
 * @see Controller
 * @see Scheduler
 * @see GanttChartWidget
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

signals:
    void processCreated(const Process&);
    void runRequested();
    void algorithmSelected(const QString& name, int quantum);
    void clearProcessesRequested();
    void contextSwitchChanged(int cs);
    void modeSelected(const QString& name);
    void threadQuantumChanged(int q);

public slots:
    void showProcesses(const std::vector<Process>& processes);
    void displayResult(const std::vector<Process>& processes);
    void displayGantt(const std::vector<GanttEntry>& gantt);

private slots:
    void onAddProcess();
    void onRun();
    void onClear();
    void onAlgorithmChanged(int);
    void onQuantumChanged(int);
    void onModeChanged(int);
    void onThreadQuantumChanged(int);
    void onContextSwitchChanged(int);

private:
    Ui::MainWindow* ui;
    int m_nextPid{1};
};
