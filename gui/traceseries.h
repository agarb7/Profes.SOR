#ifndef TRACESERIES_H
#define TRACESERIES_H

#include "model/types_.h"

#include <QLineSeries>

#include <limits>

/*!
 * \brief The TraceSeries class
 *
 * Use only \lTraceSeries::replace for any modify operation for suport min and max consistency
 */
class TraceSeries : public QtCharts::QLineSeries
{
    Q_OBJECT
public:
    explicit TraceSeries(QObject *parent = 0);

    void replace(const Model::PointVector &modelPoints, double sampleSpacing);

    bool hasBounds() const;

    double minX() const;
    double maxX() const;

    double minY() const;
    double maxY() const;

    QRectF valueRect() const;

private:
    double m_minY = 0;
    double m_maxY = 0;
};

#endif // TRACESERIES_H
