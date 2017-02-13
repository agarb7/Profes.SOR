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
    connect(parent, &QChart::plotAreaChanged,
            this, &ChartSelection::updateGeometry);

    connect(axisX(), &QValueAxis::rangeChanged,
            this, &ChartSelection::updateGeometry);

    connect(axisY(), &QValueAxis::rangeChanged,
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

double ChartSelection::start() const
{
    return m_start;
}

double ChartSelection::end() const
{
    return m_end;
}

double ChartSelection::min() const
{
    return std::min(m_start, m_end);
}

double ChartSelection::max() const
{
    return std::max(m_start, m_end);
}

void ChartSelection::setStart(double start)
{
    if (m_start != start) {
        m_start = start;
        updateGeometry();
        emit startChanged(m_start);
    }
}

void ChartSelection::setEnd(double end)
{
    if (m_end != end) {
        m_end = end;
        updateGeometry();
        emit endChanged(m_end);
    }
}

void ChartSelection::setPosition(double pos)
{
    bool startMod = false;
    bool endMod = false;

    if ((startMod = m_start != pos))
        m_start = pos;

    if ((endMod = m_end != pos))
        m_end = pos;

    if (startMod || endMod)
        updateGeometry();

    if (startMod)
        emit startChanged(m_start);

    if (endMod)
        emit endChanged(m_end);
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
