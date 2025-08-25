/**
 * \file ganttchartwidget.cpp
 * \brief Auto-generated documentation header for ganttchartwidget.cpp.
 * \details This file is part of the Scheduling Simulator project and was annotated for Doxygen.
 * \copyright
 *   (c) Scheduling Simulator contributors. All rights reserved.
 * \date 2025-08-24
 */

#include "ganttchartwidget.hpp"
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QFontMetrics>

GanttChartWidget::GanttChartWidget(QWidget* parent)
    : QGraphicsView(parent), m_scene(new QGraphicsScene(this))
{
    setScene(m_scene);
    setRenderHint(QPainter::Antialiasing, true);
    setMinimumHeight(140);
}

QColor GanttChartWidget::colorFor(int pid, int tid) {
    qint64 key = ( (qint64)pid << 32 ) | (qint64)(tid+1);
    if (m_keyColors.contains(key)) return m_keyColors.value(key);
    // deterministic-ish color
    int h = ( (pid*73) ^ ((tid+1)*127) ) % 360;
    QColor c; c.setHsv(h, 180, 200);
    m_keyColors.insert(key, c);
    return c;
}

void GanttChartWidget::setGantt(const std::vector<GanttEntry>& entries) {
    m_scene->clear();
    if (entries.empty()) return;

    // compute total span
    int tmin = entries.front().start;
    int tmax = entries.front().end;
    for (const auto& e : entries) { tmin = std::min(tmin, e.start); tmax = std::max(tmax, e.end); }
    if (tmin<0) tmin = 0;
    int span = std::max(1, tmax - tmin);

    const int H = 50;            // bar height
    const int MARGIN = 20;
    const double W = 800.0;      // base width
    const double pxPerUnit = W / span;

    // draw bars
    int y = 0;
    QFont f; f.setBold(true);
    for (const auto& e : entries) {
        double x = (e.start - tmin) * pxPerUnit + MARGIN;
        double w = (e.end - e.start) * pxPerUnit;
        QRectF rect(x, MARGIN, w, H);
        QColor c = colorFor(e.pid, e.tid);
        auto *ri = m_scene->addRect(rect, QPen(Qt::NoPen), QBrush(c));
        QString label = (e.tid >= 0)
            ? QString("P%1:T%2").arg(e.pid).arg(e.tid)
            : QString("P%1").arg(e.pid);
        auto *ti = m_scene->addSimpleText(label);
        ti->setFont(f);
        QFontMetrics fm(f);
        ti->setPos(rect.center().x() - fm.horizontalAdvance(label)/2.0, rect.center().y() - fm.height()/2.0);
        y += H + 4;
    }

    // draw time axis ticks (every 5 units or so)
    const int TICK_H = 18;
    for (int t = tmin; t <= tmax; t += std::max(1, span/8)) {
        double x = (t - tmin) * pxPerUnit + MARGIN;
        m_scene->addLine(x, MARGIN + H + 8, x, MARGIN + H + 8 + TICK_H, QPen(Qt::gray));
        auto *txt = m_scene->addSimpleText(QString::number(t));
        txt->setPos(x-4, MARGIN + H + 8 + TICK_H);
    }

    // fit view
    setSceneRect(0, 0, W + 2*MARGIN, MARGIN + H + 8 + TICK_H + 24);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
