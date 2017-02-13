#ifndef TRACEVIEW_H
#define TRACEVIEW_H

#include "model/types_.h"

#include <QAbstractItemView>

namespace QtCharts {
    class QValueAxis;
}

class TraceChart;
class TraceSelectionItem;

class TraceView : public QAbstractItemView
{
    Q_OBJECT

    Q_PROPERTY(double horizontalResolution READ horizontalResolution WRITE setHorizontalResolution NOTIFY horizontalResolutionChanged)
    Q_PROPERTY(double verticalResolution READ verticalResolution WRITE setVerticalResolution NOTIFY verticalResolutionChanged)

    Q_PROPERTY(bool useAll READ useAll WRITE setUseAll NOTIFY useAllToggled)
public:
    explicit TraceView(QWidget *parent = 0);

    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
    QModelIndex indexAt(const QPoint &point) const override;

    TraceSelectionItem *traceSelection() const;

    double horizontalResolution() const;
    double verticalResolution() const;

    bool useAll() const;
    void setUseAll(bool useAll);

signals:
    void horizontalResolutionChanged(double pixelPerMeter);
    void verticalResolutionChanged(double pixelPerDb);
    void useAllToggled(bool toggle);

public slots:
    void setCurrentRow(int row);

    void setHorizontalResolution(double pixelPerMeter);
    void setVerticalResolution(double pixelPerDb);

    void deleteSelected();
    void duplicateSelected();

protected slots:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) override;
    void rowsInserted(const QModelIndex &parent, int start, int end) override;
    void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end) override;    

protected:
    void scrollContentsBy(int dx, int dy) override;

    QModelIndex moveCursor(CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers) override;

    int horizontalOffset() const override;
    int verticalOffset() const override;

    bool isIndexHidden(const QModelIndex &index) const override;

    void setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags command) override;

    QRegion visualRegionForSelection(const QItemSelection &selection) const override;

    void resizeEvent(QResizeEvent *) override;
    void showEvent(QShowEvent *) override;

private:
    Model::PointVector points(int row) const;
    void setPoints(int row, const Model::PointVector &points);

    double sampleSpacing(int row) const;

    template <class T>
    T value(int row, int column) const;

    template <class Op>
    void forAffectedRows(Op op) const;

    void updateAxes();
    void updateScrollBars();
    void updateVisability();

    void setResolution(double resolution, double oldResolution,
                       QtCharts::QValueAxis *axis, const QByteArray &signal);

    void emitResolutionsChanged();

    void setCurrent(const QModelIndex &index, bool current);

    int selectionMinIndex(int row) const;
    int selectionMaxIndex(int row) const;

    static void setupScrollBar(QScrollBar *bar,
                               double axisMin, double axisMax,
                               double seriesMin, double seriesMax);

    static void setupAxis(QtCharts::QValueAxis *axis, const QScrollBar *bar,
                          double seriesMin, double seriesMax);

    static double resolution(double plotLength, const QtCharts::QValueAxis *axis);

    bool m_useAll = false;
    TraceChart *m_chart;    

    static const int m_pointsColumn;
    static const int m_sampleSpacingColumn;
};

#endif // TRACEVIEW_H
