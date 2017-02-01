#ifndef GRAPHICSGRIDITEM_H
#define GRAPHICSGRIDITEM_H

#include "graphicstraceitem.h"

#include <QGraphicsItem>

class GraphicsGridItem : public QGraphicsItem
{
public:
    explicit GraphicsGridItem(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem */*option*/,
                       QWidget */*widget*/);

    void fitIn(const QRectF &rect);

    GraphicsTraceItem *traceItem() const;
    void setTraceItem(GraphicsTraceItem *traceItem);

private:
    QRectF m_geometry;
    GraphicsTraceItem *m_traceItem = 0;
};

#endif // GRAPHICSGRIDITEM_H
