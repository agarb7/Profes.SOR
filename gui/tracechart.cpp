#include "tracechart.h"

#include "traceselectionitem.h"
#include "traceseries.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLayout>
#include <QValueAxis>

#include <algorithm>
#include <tuple>

using namespace QtCharts;

TraceChart::TraceChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags)
{
    setBackgroundRoundness(0);
    legend()->hide();
    setMargins(QMargins());
    layout()->setContentsMargins(0,0,0,0);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 1000);
    axisX->setTitleText("m");
    setAxisX(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-50, 0);
    axisY->setTitleText("dB");
    setAxisY(axisY);

    m_selection = new TraceSelectionItem(this);

    m_selection->setZValue(2);
}

QValueAxis *TraceChart::valueAxisX() const
{
    return static_cast<QValueAxis*>(axisX());
}

QValueAxis *TraceChart::valueAxisY() const
{
    return static_cast<QValueAxis*>(axisY());
}

const TraceSeries *TraceChart::series(int index) const
{
    return m_series.value(index);
}

void TraceChart::addSeries(int index, const Model::PointVector &modelPoints, double sampleSpacing)
{
    auto series = new TraceSeries;
    addSeriesAxesAware(series);
    m_series[index] = series;    

    series->replace(modelPoints, sampleSpacing);
    updateVisibleBounds();

    QPen pen;
    pen.setColor(m_seriesColor);
    pen.setWidth(1);

    series->setPen(pen);
}

void TraceChart::updateSeries(int index, const Model::PointVector &modelPoints, double sampleSpacing)
{
    Q_CHECK_PTR(m_series.value(index));

    TraceSeries *series = m_series[index];
    series->replace(modelPoints, sampleSpacing);

    updateVisibleBounds();
}

void TraceChart::removeSeries(int index)
{
    delete m_series.take(index);

    updateVisibleBounds();
}

void TraceChart::highlightSeries(int index, bool highlight)
{
    Q_CHECK_PTR(m_series.value(index));

    TraceSeries *series = m_series[index];

    //hack for bring to top
    if (highlight) {
        removeSeriesAxesAware(series);
        addSeriesAxesAware(series);
        series->setColor(m_highlightSeriesColor);
    }
    else {
        series->setColor(m_seriesColor);
    }
}

void TraceChart::setSeriesVisible(bool visible)
{    
    for (auto series: m_series)
        series->setVisible(visible);

    updateVisibleBounds();    
}

void TraceChart::setSeriesVisible(int index, bool visible)
{
    Q_CHECK_PTR(m_series.value(index));

    m_series[index]->setVisible(visible);
    updateVisibleBounds();
}

void TraceChart::setSeriesVisible(QList<int> indices, bool visible)
{
    for (int index: indices) {
        Q_CHECK_PTR(m_series.value(index));

        m_series[index]->setVisible(visible);
    }

    updateVisibleBounds();
}

TraceSelectionItem *TraceChart::selection() const
{
    return m_selection;
}

QRectF TraceChart::visibleSeriesValueRect() const
{
    return m_visSeriesRect;
}

double TraceChart::visibleSeriesMinX() const
{
    return m_visSeriesRect.left();
}

double TraceChart::visibleSeriesMaxX() const
{
    return m_visSeriesRect.right();
}

double TraceChart::visibleSeriesMinY() const
{
    return m_visSeriesRect.top();
}

double TraceChart::visibleSeriesMaxY() const
{
    return m_visSeriesRect.bottom();
}

void TraceChart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_selection->setPosition(mapToValue(event->pos()).x());
}

void TraceChart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_selection->setEnd(mapToValue(event->pos()).x());
}

void TraceChart::addSeriesAxesAware(TraceSeries *series)
{
    QChart::addSeries(series);

    series->attachAxis(axisX());
    series->attachAxis(axisY());
}

void TraceChart::removeSeriesAxesAware(TraceSeries *series)
{
    series->detachAxis(axisX());
    series->detachAxis(axisY());

    QChart::removeSeries(series);
}

void TraceChart::updateVisibleBounds()
{
    QRectF oldRect = m_visSeriesRect;
    m_visSeriesRect = QRectF();

    auto it = m_series.cbegin();
    auto end = m_series.cend();

    while(it != end) {
        if ((*it)->hasBounds() && (*it)->isVisible()) {
            m_visSeriesRect = (*it)->valueRect();
            ++it;
            break;
        }

        ++it;
    }

    for (; it != end; ++it) {
        if (!(*it)->hasBounds() || !(*it)->isVisible())
            continue;

        m_visSeriesRect |= (*it)->valueRect();
    }

    if (oldRect != m_visSeriesRect)
        emit visibleSeriesValueRectChanged(m_visSeriesRect);
}
