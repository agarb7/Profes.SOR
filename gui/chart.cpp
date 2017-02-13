#include "chart.h"

#include "chartselection.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLayout>
#include <QValueAxis>

using namespace QtCharts;

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags)
{
    setBackgroundRoundness(0);
    legend()->hide();
    setMargins(QMargins());
    layout()->setContentsMargins(0,0,0,0);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, m_baseLength);
    axisX->setTitleText("m");
    setAxisX(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-50, 0);
    axisY->setTitleText("dB");
    setAxisY(axisY);

    m_selection = new ChartSelection(this);

    m_selection->setZValue(2);
}

void Chart::addSeries(QAbstractSeries *series)
{
    QChart::addSeries(series);

    series->attachAxis(axisX());
    series->attachAxis(axisY());
}

ChartSelection *Chart::selection() const
{
    return m_selection;
}

void Chart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_selection->setPosition(mapToValue(event->pos()).x());
}

void Chart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_selection->setEnd(mapToValue(event->pos()).x());
}
