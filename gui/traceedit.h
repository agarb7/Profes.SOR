#ifndef TRACEEDIT_H
#define TRACEEDIT_H

#include "model/types_.h"

#include <QChartView>
#include <QLineSeries>

class Chart;

class TraceEdit : public QtCharts::QChartView
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

    Chart *chart() const;

public slots:
    void horizontalScrollTo(double part);
    void setHorizontalZoom(double factor);

    void deleteSelected();
    void duplicateSelected();

signals:
    void pointsChanged(const Model::PointVector &points);
    void sampleSpacingChanged(double spacing);

private:    
    void updateSeries();
    double indexToValue(int index) const;
    int selectionMinIndex() const;
    int selectionMaxIndex() const;

    Model::PointVector m_points;
    double m_sampleSpacing=0;
    QtCharts::QLineSeries m_series;

    double m_baseLength = 1000;
};

#endif // TRACEEDIT_H
