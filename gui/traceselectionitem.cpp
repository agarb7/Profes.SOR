#include "traceselectionitem.h"

#include <QPainter>

#include <cmath>

using namespace QtCharts;

/*!
 * \brief ChartSelection::ChartSelection
 * \param parent must be not null and have x-axis
 */
TraceSelectionItem::TraceSelectionItem(QChart *parent) :
    QGraphicsObject(parent)
{
    connect(parent, &QChart::plotAreaChanged,
            this, &TraceSelectionItem::updateGeometry);

    connect(axisX(), &QValueAxis::rangeChanged,
            this, &TraceSelectionItem::updateGeometry);

    connect(axisY(), &QValueAxis::rangeChanged,
            this, &TraceSelectionItem::updateGeometry);
}

QRectF TraceSelectionItem::boundingRect() const
{
    return m_boundingRect;
}

void TraceSelectionItem::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem */*option*/,
                           QWidget */*widget*/)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,0,0,200));
    painter->setBrush(brush);

    painter->drawRect(m_boundingRect);
}

double TraceSelectionItem::start() const
{
    return m_start;
}

double TraceSelectionItem::end() const
{
    return m_end;
}

double TraceSelectionItem::min() const
{
    return std::min(m_start, m_end);
}

double TraceSelectionItem::max() const
{
    return std::max(m_start, m_end);
}

void TraceSelectionItem::setStart(double start)
{
    if (m_start != start) {
        m_start = start;
        updateGeometry();
        emit startChanged(m_start);
    }
}

void TraceSelectionItem::setEnd(double end)
{
    if (m_end != end) {
        m_end = end;
        updateGeometry();
        emit endChanged(m_end);
    }
}

void TraceSelectionItem::setPosition(double pos)
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

QValueAxis *TraceSelectionItem::axisX() const
{
    return static_cast<QValueAxis*>(chart()->axisX());
}

QValueAxis *TraceSelectionItem::axisY() const
{
    return static_cast<QValueAxis*>(chart()->axisY());
}

QChart *TraceSelectionItem::chart() const
{
    return static_cast<QChart*>(parentItem());
}

void TraceSelectionItem::updateGeometry()
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
