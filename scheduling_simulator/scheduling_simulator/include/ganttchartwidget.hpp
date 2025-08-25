/**
 * \file ganttchartwidget.hpp
 * \brief Auto-generated documentation header for ganttchartwidget.hpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include <QColor>
#include <vector>
#include "ganttentry.hpp"/**
 * @class GanttChartWidget
 * @brief Qt widget that renders a Gantt chart from @ref GanttEntry data.
 */



class GanttChartWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit GanttChartWidget(QWidget* parent = nullptr);
    void setGantt(const std::vector<GanttEntry>& entries);

private:
    QGraphicsScene* m_scene{nullptr};
    QMap<qint64, QColor> m_keyColors; // key = pid<<32 | (tid+1)

    QColor colorFor(int pid, int tid);
};
