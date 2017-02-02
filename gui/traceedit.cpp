#include "traceedit.h"

#include <QGraphicsScene>
#include <QResizeEvent>
#include <QList>
#include <QPointF>
#include <QChart>
#include <QValueAxis>
#include <QGraphicsLayout>

#include <QDebug>

#include <algorithm>

using namespace QtCharts;

TraceEdit::TraceEdit(QWidget *parent) :
    QChartView(parent)
{
    qRegisterMetaType<Model::PointVector>("Model::PointVector");

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);

    m_series.setPen(pen);

    QChart *ch = chart();
    ch->setBackgroundRoundness(0);
    ch->legend()->hide();
    ch->setMargins(QMargins());
    ch->layout()->setContentsMargins(0,0,0,0);

    ch->addSeries(&m_series);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, m_baseLength);
    axisX->setTitleText("m");
    ch->setAxisX(axisX, &m_series);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-50, 0);
    axisY->setTitleText("dB");
    ch->setAxisY(axisY, &m_series);    
}

Model::PointVector TraceEdit::points() const
{
    return m_points;
}

void TraceEdit::setPoints(const Model::PointVector &points)
{
    m_points = points;
    updateSampleSeries();

    emit pointsChanged(points);
}

double TraceEdit::sampleSpacing() const
{
    return m_sampleSpacing;
}

void TraceEdit::setSampleSpacing(double spacing)
{
    m_sampleSpacing = spacing;
    updateSampleSeries();

    emit sampleSpacingChanged(spacing);
}

void TraceEdit::horizontalScrollTo(double part)
{    
    int count = m_points.count();
    if (count==0)
        return;

    QChart *ch = chart();
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
    QChart *ch = chart();

    auto axis = static_cast<QValueAxis*>(ch->axisX());

    double newLength = m_baseLength/factor;
    double newMax = axis->min() + newLength;

    axis->setMax(newMax);
}

void TraceEdit::updateSampleSeries()
{
    int count = m_points.count();
    QList<QPointF> points;

    for (int i=0; i<count; ++i) {
        points.push_back(QPointF(
            i*m_sampleSpacing,
            m_points.at(i)
        ));
    }

    m_series.replace(points);    
}
