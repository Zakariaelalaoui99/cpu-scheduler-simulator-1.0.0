/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ganttchartwidget.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTableWidget *processTable;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *labelArrival;
    QLineEdit *arrivalEdit;
    QLabel *labelBurst;
    QLineEdit *burstEdit;
    QLabel *labelPriority;
    QSpinBox *prioritySpin;
    QPushButton *addButton;
    QLabel *labelAlg;
    QComboBox *algorithmBox;
    QLabel *labelQuantum;
    QSpinBox *quantumSpin;
    QLabel *labelMode;
    QComboBox *modeBox;
    QLabel *labelTQ;
    QSpinBox *threadQuantumSpin;
    QLabel *labelCS;
    QSpinBox *contextSwitchSpin;
    QPushButton *startButton;
    QPushButton *resetButton;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *statsLabel;
    QLabel *simuTimeLabel;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    GanttChartWidget *ganttWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(595, 750);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        processTable = new QTableWidget(groupBox);
        processTable->setObjectName("processTable");

        verticalLayout->addWidget(processTable);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName("formLayout");
        labelArrival = new QLabel(groupBox_2);
        labelArrival->setObjectName("labelArrival");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelArrival);

        arrivalEdit = new QLineEdit(groupBox_2);
        arrivalEdit->setObjectName("arrivalEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, arrivalEdit);

        labelBurst = new QLabel(groupBox_2);
        labelBurst->setObjectName("labelBurst");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelBurst);

        burstEdit = new QLineEdit(groupBox_2);
        burstEdit->setObjectName("burstEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, burstEdit);

        labelPriority = new QLabel(groupBox_2);
        labelPriority->setObjectName("labelPriority");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelPriority);

        prioritySpin = new QSpinBox(groupBox_2);
        prioritySpin->setObjectName("prioritySpin");
        prioritySpin->setMinimum(0);
        prioritySpin->setMaximum(100);

        formLayout->setWidget(2, QFormLayout::FieldRole, prioritySpin);

        addButton = new QPushButton(groupBox_2);
        addButton->setObjectName("addButton");

        formLayout->setWidget(3, QFormLayout::LabelRole, addButton);

        labelAlg = new QLabel(groupBox_2);
        labelAlg->setObjectName("labelAlg");

        formLayout->setWidget(4, QFormLayout::LabelRole, labelAlg);

        algorithmBox = new QComboBox(groupBox_2);
        algorithmBox->setObjectName("algorithmBox");

        formLayout->setWidget(4, QFormLayout::FieldRole, algorithmBox);

        labelQuantum = new QLabel(groupBox_2);
        labelQuantum->setObjectName("labelQuantum");

        formLayout->setWidget(5, QFormLayout::LabelRole, labelQuantum);

        quantumSpin = new QSpinBox(groupBox_2);
        quantumSpin->setObjectName("quantumSpin");
        quantumSpin->setMinimum(1);
        quantumSpin->setMaximum(1000);

        formLayout->setWidget(5, QFormLayout::FieldRole, quantumSpin);

        labelMode = new QLabel(groupBox_2);
        labelMode->setObjectName("labelMode");

        formLayout->setWidget(6, QFormLayout::LabelRole, labelMode);

        modeBox = new QComboBox(groupBox_2);
        modeBox->setObjectName("modeBox");

        formLayout->setWidget(6, QFormLayout::FieldRole, modeBox);

        labelTQ = new QLabel(groupBox_2);
        labelTQ->setObjectName("labelTQ");

        formLayout->setWidget(7, QFormLayout::LabelRole, labelTQ);

        threadQuantumSpin = new QSpinBox(groupBox_2);
        threadQuantumSpin->setObjectName("threadQuantumSpin");
        threadQuantumSpin->setMinimum(1);
        threadQuantumSpin->setMaximum(1000);

        formLayout->setWidget(7, QFormLayout::FieldRole, threadQuantumSpin);

        labelCS = new QLabel(groupBox_2);
        labelCS->setObjectName("labelCS");

        formLayout->setWidget(8, QFormLayout::LabelRole, labelCS);

        contextSwitchSpin = new QSpinBox(groupBox_2);
        contextSwitchSpin->setObjectName("contextSwitchSpin");
        contextSwitchSpin->setMinimum(0);
        contextSwitchSpin->setMaximum(1000);

        formLayout->setWidget(8, QFormLayout::FieldRole, contextSwitchSpin);

        startButton = new QPushButton(groupBox_2);
        startButton->setObjectName("startButton");

        formLayout->setWidget(9, QFormLayout::LabelRole, startButton);

        resetButton = new QPushButton(groupBox_2);
        resetButton->setObjectName("resetButton");

        formLayout->setWidget(9, QFormLayout::FieldRole, resetButton);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        statsLabel = new QLabel(groupBox_3);
        statsLabel->setObjectName("statsLabel");

        verticalLayout_2->addWidget(statsLabel);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        simuTimeLabel = new QLabel(centralwidget);
        simuTimeLabel->setObjectName("simuTimeLabel");
        simuTimeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(simuTimeLabel, 1, 1, 1, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        ganttWidget = new GanttChartWidget(groupBox_4);
        ganttWidget->setObjectName("ganttWidget");

        verticalLayout_3->addWidget(ganttWidget);


        gridLayout->addWidget(groupBox_4, 2, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CPU Task Scheduler Simulator", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Process Table", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Controls", nullptr));
        labelArrival->setText(QCoreApplication::translate("MainWindow", "Arrival Time", nullptr));
        labelBurst->setText(QCoreApplication::translate("MainWindow", "Burst Time", nullptr));
        labelPriority->setText(QCoreApplication::translate("MainWindow", "Priority", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Insert Process", nullptr));
        labelAlg->setText(QCoreApplication::translate("MainWindow", "Algorithm", nullptr));
        labelQuantum->setText(QCoreApplication::translate("MainWindow", "Quantum", nullptr));
        labelMode->setText(QCoreApplication::translate("MainWindow", "Scheduling Mode", nullptr));
        labelTQ->setText(QCoreApplication::translate("MainWindow", "Thread Quantum", nullptr));
        labelCS->setText(QCoreApplication::translate("MainWindow", "Context Switch", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start Simulation", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Statistics", nullptr));
        simuTimeLabel->setText(QCoreApplication::translate("MainWindow", "Simulation Time:", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Gantt Chart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
