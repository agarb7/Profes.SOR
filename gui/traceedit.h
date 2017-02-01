#ifndef TRACEEDIT_H
#define TRACEEDIT_H

#include "graphicstraceitem.h"
#include "graphicsgriditem.h"

#include "model/types_.h"

#include <QGraphicsView>

class TraceEdit : public QGraphicsView
{
    Q_OBJECT

    Q_PROPERTY(Model::PointVector points
               READ points
               WRITE setPoints
               NOTIFY pointsChanged
               USER true)

    Q_PROPERTY(double sampleSpacing
               READ sampleSpacing
               WRITE setSampleSpacing
               NOTIFY sampleSpacingChanged)

public:
    explicit TraceEdit(QWidget *parent = 0);

    Model::PointVector points() const;
    void setPoints(const Model::PointVector &points);

    double sampleSpacing() const;
    void setSampleSpacing(double spacing);    

signals:
    void pointsChanged(const Model::PointVector &points);
    void sampleSpacingChanged(double spacing);

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    void updateScene();

    GraphicsGridItem m_gridItem;
    GraphicsTraceItem m_traceItem;
};

#endif // TRACEEDIT_H
