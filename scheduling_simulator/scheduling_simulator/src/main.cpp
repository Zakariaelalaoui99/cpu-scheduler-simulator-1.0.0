/**
 * \file main.cpp
 * \brief Auto-generated documentation header for main.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include <QApplication>
#include "mainwindow.hpp"
#include "controller.hpp"
#include "scheduler.hpp"
#include "fcfs.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/icons/app_icon.png"));  // aus resources.qrc
    auto algorithm = std::make_unique<FCFS>();
    Scheduler scheduler(std::move(algorithm));
    MainWindow window;
    Controller controller(&scheduler, &window);

    QObject::connect(&window, &MainWindow::processCreated, &controller, &Controller::handleProcessCreation);
    QObject::connect(&window, &MainWindow::algorithmSelected, &controller, &Controller::handleAlgorithmSelection);
    QObject::connect(&window, &MainWindow::runRequested, &controller, &Controller::handleExecution);
    QObject::connect(&window, &MainWindow::clearProcessesRequested, &controller, &Controller::handleClearProcesses);
    QObject::connect(&window, &MainWindow::contextSwitchChanged, &controller, &Controller::handleContextSwitchChanged);
    QObject::connect(&window, &MainWindow::modeSelected, &controller, &Controller::handleModeSelected);
    QObject::connect(&window, &MainWindow::threadQuantumChanged, &controller, &Controller::handleThreadQuantumChanged);

    window.show();
    return app.exec();
}
