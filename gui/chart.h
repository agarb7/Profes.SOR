#ifndef CHART_H
#define CHART_H

#include <QChart>

class ChartSelection;

class Chart: public QtCharts::QChart
{
    Q_OBJECT

public:
    explicit Chart(QGraphicsItem *parent = 0,
                   Qt::WindowFlags wFlags = Qt::WindowFlags());

    void addSeries(QtCharts::QAbstractSeries *series);

    ChartSelection *selection() const;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);    

private:
    ChartSelection *m_selection = 0;

    double m_baseLength = 1000;
};

#endif // CHART_H
