#include "chartselection.h"

#include <QPainter>

#include <cmath>

using namespace QtCharts;

/*!
 * \brief ChartSelection::ChartSelection
 * \param parent must be not null and have x-axis
 */
ChartSelection::ChartSelection(QChart *parent) :
    QGraphicsObject(parent)
{
    connect(axisX(), &QValueAxis::rangeChanged,
            this, &ChartSelection::updateGeometry);
}

QRectF ChartSelection::boundingRect() const
{
    return m_boundingRect;
}

void ChartSelection::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem */*option*/,
                           QWidget */*widget*/)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,0,0,200));
    painter->setBrush(brush);

    painter->drawRect(m_boundingRect);
}

double ChartSelection::min() const
{
    return std::min(m_start, m_end);
}

void ChartSelection::setStart(double start)
{
    m_start = m_end = start;
    updateGeometry();
}

double ChartSelection::max() const
{
    return std::max(m_start, m_end);
}

void ChartSelection::setEnd(double end)
{
    m_end = end;
    updateGeometry();
}

QValueAxis *ChartSelection::axisX() const
{
    return static_cast<QValueAxis*>(chart()->axisX());
}

QValueAxis *ChartSelection::axisY() const
{
    return static_cast<QValueAxis*>(chart()->axisY());
}

QChart *ChartSelection::chart() const
{
    return static_cast<QChart*>(parentItem());
}

void ChartSelection::updateGeometry()
{
    prepareGeometryChange();

    QValueAxis *axisX = this->axisX();

    double valueLeft  = std::max(min(), axisX->min());
    double valueRight = std::min(max(), axisX->max());

    if (valueLeft > valueRight) {
        m_boundingRect.setRect(0,0,0,0);

        return;
    }

    QChart *chart = this->chart();
    QValueAxis *axisY = this->axisY();

    QPointF topLeft =chart->mapToPosition(QPointF(
        valueLeft,
        axisY->max()
    ));

    QPointF bottomRight = chart->mapToPosition(QPointF(
        valueRight,
        axisY->min()
    ));

    m_boundingRect.setTopLeft(topLeft);
    m_boundingRect.setBottomRight(bottomRight);
}
