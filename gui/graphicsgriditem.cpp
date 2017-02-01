#include "graphicsgriditem.h"

#include <QPainter>

GraphicsGridItem::GraphicsGridItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{    
}

QRectF GraphicsGridItem::boundingRect() const
{
    return m_geometry;
}

void GraphicsGridItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem */*option*/,
                             QWidget */*widget*/)
{
    int abcY = m_geometry.height()-10;
    painter->drawLine(10, 0, 10, abcY);
    painter->drawLine(10, abcY, m_geometry.width(), abcY);
}

void GraphicsGridItem::fitIn(const QRectF &rect)
{
    prepareGeometryChange();

    double width = m_traceItem
            ? qMax(m_traceItem->boundingRect().width(), rect.width())
            : rect.width();

    m_geometry = QRectF(rect.x(), rect.y(),
                        width, rect.height());
}


GraphicsTraceItem *GraphicsGridItem::traceItem() const
{
    return m_traceItem;
}

void GraphicsGridItem::setTraceItem(GraphicsTraceItem *traceItem)
{
    prepareGeometryChange();

    m_traceItem = traceItem;
    m_traceItem->setParentItem(this);
    m_traceItem->setPos(10, 0);
}
