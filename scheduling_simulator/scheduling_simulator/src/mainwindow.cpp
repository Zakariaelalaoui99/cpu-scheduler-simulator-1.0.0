/**
 * \file mainwindow.cpp
 * \brief Auto-generated documentation header for mainwindow.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QComboBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // fill algorithm choices
    ui->algorithmBox->addItems({"FCFS","SJF","RR","RRP"});
    ui->modeBox->addItems({"Process Only","Kernel-Level Threads","User-Level Threads"});
    ui->quantumSpin->setValue(2);
    ui->threadQuantumSpin->setValue(1);
    ui->contextSwitchSpin->setValue(0);

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddProcess);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onRun);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onClear);
    connect(ui->algorithmBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onAlgorithmChanged);
    connect(ui->quantumSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onQuantumChanged);
    connect(ui->modeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onModeChanged);
    connect(ui->threadQuantumSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onThreadQuantumChanged);
    connect(ui->contextSwitchSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onContextSwitchChanged);

    onAlgorithmChanged(ui->algorithmBox->currentIndex());
    onModeChanged(ui->modeBox->currentIndex());
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::onAddProcess() {
    bool ok1, ok2, ok3;
    int arrival = ui->arrivalEdit->text().toInt(&ok1);
    int burst   = ui->burstEdit->text().toInt(&ok2);
    int prio    = ui->prioritySpin->value(); ok3=true;
    if (!ok1 || !ok2 || burst<=0) {
        QMessageBox::warning(this, "Input Error", "Please enter valid Arrival/Burst (burst>0).");
        return;
    }
    Process p(m_nextPid++, arrival, burst, prio);
    emit processCreated(p);
}

void MainWindow::onRun() { emit runRequested(); }
void MainWindow::onClear() { emit clearProcessesRequested(); ui->statsLabel->clear(); ui->simuTimeLabel->clear(); }

void MainWindow::onAlgorithmChanged(int) {
    const QString name = ui->algorithmBox->currentText();
    const bool needsQ = (name=="RR" || name=="RRP");
    ui->quantumSpin->setEnabled(needsQ);
    emit algorithmSelected(name, ui->quantumSpin->value());
}
void MainWindow::onQuantumChanged(int v) {
    Q_UNUSED(v);
    emit algorithmSelected(ui->algorithmBox->currentText(), ui->quantumSpin->value());
}
void MainWindow::onModeChanged(int) {
    emit modeSelected(ui->modeBox->currentText());
}
void MainWindow::onThreadQuantumChanged(int q) { emit threadQuantumChanged(q); }
void MainWindow::onContextSwitchChanged(int cs) { emit contextSwitchChanged(cs); }

void MainWindow::showProcesses(const std::vector<Process>& processes) {
    ui->processTable->setRowCount((int)processes.size());
    ui->processTable->setColumnCount(5);
    QStringList headers; headers << "PID" << "Arrival" << "Burst" << "Prio" << "Completion";
    ui->processTable->setHorizontalHeaderLabels(headers);
    int r=0;
    for (const auto& p : processes) {
        ui->processTable->setItem(r,0,new QTableWidgetItem(QString::number(p.getPid())));
        ui->processTable->setItem(r,1,new QTableWidgetItem(QString::number(p.getArrivalTime())));
        ui->processTable->setItem(r,2,new QTableWidgetItem(QString::number(p.getBurstTime())));
        ui->processTable->setItem(r,3,new QTableWidgetItem(QString::number(p.getPriority())));
        ui->processTable->setItem(r,4,new QTableWidgetItem(QString::number(p.getCompletionTime())));
        ++r;
    }
    ui->processTable->resizeColumnsToContents();
}

void MainWindow::displayResult(const std::vector<Process>& processes) {
    if (processes.empty()) { ui->statsLabel->clear(); return; }
    double avgTA=0, avgWT=0;
    int n=0;
    for (const auto& p: processes) {
        avgTA += p.getTurnaroundTime();
        avgWT += p.getWaitingTime();
        ++n;
    }
    avgTA /= std::max(1,n);
    avgWT /= std::max(1,n);
    ui->statsLabel->setText(QString("Average Turnaround: %1\nAverage Waiting: %2")
                            .arg(avgTA).arg(avgWT));
    int makespan = 0;
    for (const auto& p: processes) makespan = std::max(makespan, p.getCompletionTime());
    ui->simuTimeLabel->setText(QString("Simulation Time: %1").arg(makespan));
}

void MainWindow::displayGantt(const std::vector<GanttEntry>& gantt) {
    // The UI has a promoted QGraphicsView named ganttView, but we keep a convenience cast.
    // In the .ui we promoted it to GanttChartWidget, objectName ganttWidget.
    ui->ganttWidget->setGantt(gantt);
}
