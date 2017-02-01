#include "traceedit.h"

#include <QGraphicsScene>
#include <QResizeEvent>

TraceEdit::TraceEdit(QWidget *parent) : QGraphicsView(parent)
{
    qRegisterMetaType<Model::PointVector>("Model::PointVector");

    m_gridItem.setTraceItem(&m_traceItem);

    auto scene = new QGraphicsScene(this);
    scene->addItem(&m_gridItem);

    setScene(scene);
}

Model::PointVector TraceEdit::points() const
{
    return m_traceItem.points();
}

void TraceEdit::setPoints(const Model::PointVector &points)
{
    m_traceItem.setPoints(points);
    updateScene();

    emit pointsChanged(points);
}

double TraceEdit::sampleSpacing() const
{
    return m_traceItem.sampleSpacing();
}

void TraceEdit::setSampleSpacing(double spacing)
{
    m_traceItem.setSampleSpacing(spacing);
    updateScene();

    emit sampleSpacingChanged(spacing);
}

void TraceEdit::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    updateScene();
}

void TraceEdit::updateScene()
{
    QRectF rect(QPointF(0,0), viewport()->size());
    m_gridItem.fitIn(rect);

    scene()->setSceneRect(m_gridItem.boundingRect());
}
