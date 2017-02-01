#ifndef GRAPHICSTRACEITEM_H
#define GRAPHICSTRACEITEM_H

#include "model/types_.h"

#include <QGraphicsItem>
#include <QPointF>

class GraphicsTraceItem : public QGraphicsItem
{    
public:
    explicit GraphicsTraceItem(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem */*option*/,
                       QWidget */*widget*/);

    Model::PointVector points() const;
    void setPoints(const Model::PointVector &points);

    double sampleSpacing() const;
    void setSampleSpacing(double spacing);

private:
    double x(int i) const;
    double y(double v) const;

    QPointF point(int i) const;

    double m_perMeter = 1;
    double m_perDb = 10;

    Model::PointVector m_points;
    double m_sampleSpacing;
};

#endif // GRAPHICSTRACEITEM_H
