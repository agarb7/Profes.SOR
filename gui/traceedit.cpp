#include "traceedit.h"

#include "chart.h"

#include <QGraphicsScene>
#include <QPointF>
#include <QValueAxis>

#include <algorithm>
#include <cmath>

using namespace QtCharts;

TraceEdit::TraceEdit(QWidget *parent) :
    QChartView(parent)
{
    qRegisterMetaType<Model::PointVector>("Model::PointVector");

    auto ch = new Chart;
    setChart(ch);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);

    m_series.setPen(pen);

    ch->addSeries(&m_series);    
}

Model::PointVector TraceEdit::points() const
{
    return m_points;
}

void TraceEdit::setPoints(const Model::PointVector &points)
{
    if (m_points == points)
        return;

    m_points = points;
    updateSeries();    

    emit pointsChanged(points);
}

double TraceEdit::sampleSpacing() const
{
    return m_sampleSpacing;
}

void TraceEdit::setSampleSpacing(double spacing)
{
    m_sampleSpacing = spacing;
    updateSeries();

    emit sampleSpacingChanged(spacing);
}

Chart *TraceEdit::chart() const
{
    return static_cast<Chart*>(QChartView::chart());
}

void TraceEdit::horizontalScrollTo(double part)
{    
    int count = m_points.count();
    if (count==0)
        return;

    Chart *ch = chart();
    auto axis = static_cast<QValueAxis*>(ch->axisX());

    double windowLength = axis->max() - axis->min();
    double minPos = m_series.at(0).x();
    double maxPos = m_series.at(count-1).x() - windowLength;

    double pos = minPos + (maxPos-minPos)*part;

    axis->setMin(pos);
    axis->setMax(pos + windowLength);
}

void TraceEdit::setHorizontalZoom(double factor)
{
    Chart *ch = chart();

    auto axis = static_cast<QValueAxis*>(ch->axisX());

    double newLength = m_baseLength/factor;
    double newMax = axis->min() + newLength;

    axis->setMax(newMax);
}

//todo allow first deletion
void TraceEdit::deleteSelected()
{
    int indFirst = selectionMinIndex();
    if (indFirst <= 0)
        return;

    int indLast = selectionMaxIndex();
    Model::PointVector ps = points();

    if (indLast >= ps.count())
        return;

    double delta = ps.at(indLast) - ps.at(indFirst-1);

    Model::PointVector res(ps.count() - (indLast-indFirst+1));

    std::copy(ps.begin(), ps.begin()+indFirst, res.begin());
    std::transform(
        ps.begin()+indLast+1,
        ps.end(),
        res.begin()+indFirst,
        [delta](double p) {
            return p-delta;
        }
    );

    setPoints(res);
}

void TraceEdit::duplicateSelected()
{
    int indFirst = selectionMinIndex();
    if (indFirst <= 0)
        return;

    int indLast = selectionMaxIndex();
    Model::PointVector ps = points();

    if (indLast >= ps.count())
        return;

    double delta = ps.at(indLast) - ps.at(indFirst-1);

    Model::PointVector res(ps.count() + (indLast-indFirst+1));

    std::copy(ps.begin(), ps.begin()+indLast+1, res.begin());
    std::transform(
        ps.begin()+indFirst,
        ps.end(),
        res.begin()+indLast+1,
        [delta](double p) {
            return p+delta;
        }
    );

    setPoints(res);
}

void TraceEdit::updateSeries()
{
    int count = m_points.count();
    QList<QPointF> points;

    for (int i=0; i<count; ++i) {
        points.push_back(QPointF(
            indexToValue(i),
            m_points.at(i)
        ));
    }

    m_series.replace(points);
}

double TraceEdit::indexToValue(int index) const
{
    return index * m_sampleSpacing;
}

int TraceEdit::selectionMinIndex() const
{
    double value = chart()->selectionMin();
    return std::lround(std::ceil(value / m_sampleSpacing));
}

int TraceEdit::selectionMaxIndex() const
{
    double value = chart()->selectionMax();
    return std::lround(std::floor(value / m_sampleSpacing));
}
