#ifndef CHARTSELECTION_H
#define CHARTSELECTION_H

#include <QChart>
#include <QValueAxis>

#include <QGraphicsObject>

class ChartSelection: public QGraphicsObject
{
    Q_OBJECT

    Q_PROPERTY(double start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(double end READ end WRITE setEnd NOTIFY endChanged)

public:
    explicit ChartSelection(QtCharts::QChart *parent);

    QRectF boundingRect() const;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem */*option*/,
               QWidget */*widget*/);

    double start() const;
    double end() const;

    double min() const;
    double max() const;

public slots:
    void setStart(double min);
    void setEnd(double max);

    void setPosition(double pos);

signals:
    void startChanged(double start);
    void endChanged(double end);

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
