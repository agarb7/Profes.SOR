#ifndef TRACECHART_H
#define TRACECHART_H

#include "model/types_.h"

#include <QChart>
#include <QHash>
#include <QColor>

#include <limits>

namespace QtCharts {
    class QValueAxis;
}

class TraceSeries;
class TraceSelectionItem;

class TraceChart: public QtCharts::QChart
{
    Q_OBJECT

public:
    explicit TraceChart(QGraphicsItem *parent = 0,
                        Qt::WindowFlags wFlags = Qt::WindowFlags());

    QtCharts::QValueAxis *valueAxisX() const;
    QtCharts::QValueAxis *valueAxisY() const;

    const TraceSeries *series(int index) const;

    void addSeries(int index, const Model::PointVector &modelPoints, double sampleSpacing);
    void updateSeries(int index, const Model::PointVector &modelPoints, double sampleSpacing);
    void removeSeries(int index);
    void highlightSeries(int index, bool highlight);
    void setSeriesVisible(bool visible);
    void setSeriesVisible(int index, bool visible);
    void setSeriesVisible(QList<int> indices, bool visible);

    TraceSelectionItem *selection() const;

    QRectF visibleSeriesValueRect() const;

    double visibleSeriesMinX() const;
    double visibleSeriesMaxX() const;
    double visibleSeriesMinY() const;
    double visibleSeriesMaxY() const;

signals:
    void visibleSeriesValueRectChanged(QRectF visibleSeriesValueRect) const;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);    

private:
    void addSeriesAxesAware(TraceSeries *series);
    void removeSeriesAxesAware(TraceSeries *series);

    void updateVisibleBounds();

    TraceSelectionItem *m_selection = 0;    

    QRectF m_visSeriesRect;

    QHash<int, TraceSeries*> m_series;

    QColor m_seriesColor = Qt::green;
    QColor m_highlightSeriesColor = Qt::red;
};

#endif // TRACECHART_H
