#include "graphicstraceitem.h"

#include <QPainter>
#include <QPainterPath>

#include <algorithm>

GraphicsTraceItem::GraphicsTraceItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemStacksBehindParent);
}

QRectF GraphicsTraceItem::boundingRect() const
{
    int count = m_points.size();
    if (count == 0)
        return QRectF();

    auto minMax = std::minmax_element(
        m_points.begin(),
        m_points.end(),
        [this](double a, double b) {return y(a)<y(b);}
    );

    return QRectF(
        QPointF(x(0), y(*minMax.second)),
        QPointF(x(count-1), y(*minMax.first))
    );
}

void GraphicsTraceItem::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem */*option*/,
                              QWidget */*widget*/)
{
    int count = m_points.size();
    if (count == 0)
        return;

    QPainterPath path;

    path.moveTo(point(0));

    for (int i=1; i<count; ++i)
        path.lineTo(point(i));

    painter->setPen(Qt::red);
    painter->drawPath(path);
}

Model::PointVector GraphicsTraceItem::points() const
{
    return m_points;
}

void GraphicsTraceItem::setPoints(const Model::PointVector &points)
{
    if (m_points != points) {
        prepareGeometryChange();
        m_points = points;
    }
}

double GraphicsTraceItem::sampleSpacing() const
{
    return m_sampleSpacing;
}

void GraphicsTraceItem::setSampleSpacing(double spacing)
{
    if (m_sampleSpacing != spacing) {
        prepareGeometryChange();
        m_sampleSpacing = spacing;
    }
}

double GraphicsTraceItem::y(double v) const
{
    return -v * m_perDb;
}

double GraphicsTraceItem::x(int i) const
{
    return i * m_sampleSpacing * m_perMeter;
}

QPointF GraphicsTraceItem::point(int i) const
{
    return QPointF(
        x(i),
        y(m_points.at(i))
    );
}
