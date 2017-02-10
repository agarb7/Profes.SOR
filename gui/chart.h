#ifndef CHART_H
#define CHART_H

#include "chartselection.h"

#include <QChart>

class Chart: public QtCharts::QChart
{
    Q_OBJECT

public:
    explicit Chart(QGraphicsItem *parent = 0,
                   Qt::WindowFlags wFlags = Qt::WindowFlags());

    void addSeries(QtCharts::QAbstractSeries *series);

    double selectionMin() const;
    double selectionMax() const;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    ChartSelection *m_selection = 0;

    double m_baseLength = 1000;
};

#endif // CHART_H
