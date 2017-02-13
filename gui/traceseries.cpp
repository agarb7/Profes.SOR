#include "traceseries.h"

#include <algorithm>
#include <tuple>

using namespace QtCharts;

TraceSeries::TraceSeries(QObject *parent) : QLineSeries(parent)
{
}

void TraceSeries::replace(const Model::PointVector &modelPoints, double sampleSpacing)
{
    Q_ASSERT(modelPoints.count()==0 || !qIsNaN(sampleSpacing));

    int count = modelPoints.count();
    QVector<QPointF> points;

    if (count) {
        auto point = [sampleSpacing](int i, double y) {
            return QPointF(i * sampleSpacing, y);
        };

        points.reserve(count);

        double y = modelPoints.at(0);
        m_minY = m_maxY = y;

        points.push_back(point(0, y));

        for (int i=1; i<count; ++i) {
            double y = modelPoints.at(i);

            std::tie(m_minY, m_maxY) = std::minmax({m_minY, y, m_maxY});

            points.push_back(point(i, y));
        }
    }

    QLineSeries::replace(points);
}

bool TraceSeries::hasBounds() const
{
    return count();
}

double TraceSeries::minX() const
{
    Q_ASSERT(hasBounds());

    return at(0).x();
}

double TraceSeries::maxX() const
{
    Q_ASSERT(hasBounds());

    return at(count()-1).x();
}

double TraceSeries::minY() const
{
    Q_ASSERT(hasBounds());

    return m_minY;
}

double TraceSeries::maxY() const
{
    Q_ASSERT(hasBounds());

    return m_maxY;
}

/*!
 * \brief TraceSeries::valueRect
 * left - minX, right - maxX, top - minY, bottom - maxY
 * \return
 */
QRectF TraceSeries::valueRect() const
{
    return QRectF(QPointF(minX(), minY()),
                  QPointF(maxX(), maxY()) );
}
