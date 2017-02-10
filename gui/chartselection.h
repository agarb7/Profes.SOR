#ifndef CHARTSELECTION_H
#define CHARTSELECTION_H

#include <QChart>
#include <QValueAxis>

#include <QGraphicsObject>

class ChartSelection: public QGraphicsObject
{
    Q_OBJECT

public:
    explicit ChartSelection(QtCharts::QChart *parent);

    QRectF boundingRect() const;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem */*option*/,
               QWidget */*widget*/);

    double min() const;
    void setStart(double min);

    double max() const;
    void setEnd(double max);

signals:


private slots:
    void updateGeometry();

private:
    QtCharts::QValueAxis *axisX() const;
    QtCharts::QValueAxis *axisY() const;

    QtCharts::QChart *chart() const;

    double m_start = 0;
    double m_end = 0;

    QRectF m_boundingRect;
};

#endif // CHARTSELECTION_H
