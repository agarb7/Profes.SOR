#include "traceview.h"

#include "tracechart.h"
#include "traceselectionitem.h"
#include "traceseries.h"

#include "model/reflectogramcolumn.h"

#include <QChartView>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QValueAxis>

#include <cmath>

using namespace QtCharts;

TraceView::TraceView(QWidget *parent) :
    QAbstractItemView(parent),
    m_chart(new TraceChart)
{
    setEditTriggers(NoEditTriggers);

    auto chartView = new QChartView(m_chart);

    auto layout = new QHBoxLayout;
    layout->addWidget(chartView);

    viewport()->setLayout(layout);

    verticalScrollBar()->setInvertedAppearance(true);
}

QRect TraceView::visualRect(const QModelIndex &index) const
{
    Q_UNUSED(index)

    //todo implement

    return QRect();
}

void TraceView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    Q_UNUSED(index)
    Q_UNUSED(hint)

    //todo implement: scroll to trace
}

QModelIndex TraceView::indexAt(const QPoint &point) const
{
    Q_UNUSED(point)

    //todo implement: return trace index containing point

    return QModelIndex();
}

TraceSelectionItem *TraceView::traceSelection() const
{    
    return m_chart->selection();
}

double TraceView::horizontalResolution() const
{
    return resolution(m_chart->plotArea().width(), m_chart->valueAxisX());
}

double TraceView::verticalResolution() const
{
    return resolution(m_chart->plotArea().height(), m_chart->valueAxisY());
}

void TraceView::setCurrentRow(int row)
{    
    Q_CHECK_PTR(model());

    QModelIndex index = model()->index(row, 0);
    setCurrentIndex(index);
}

void TraceView::setHorizontalResolution(double pixelPerMeter)
{
    setResolution(pixelPerMeter, horizontalResolution(),
                  m_chart->valueAxisX(), "horizontalResolutionChanged");
}

void TraceView::setVerticalResolution(double pixelPerDb)
{
    setResolution(pixelPerDb, verticalResolution(),
                  m_chart->valueAxisY(), "verticalResolutionChanged");
}

//todo allow first deletion
void TraceView::deleteSelected()
{
    forAffectedRows([this](int row) {
        int indFirst = selectionMinIndex(row);
        if (indFirst <= 0)
            return;

        int indLast = selectionMaxIndex(row);
        Model::PointVector ps = points(row);

        if (indLast >= ps.count())
            return;

        double delta = ps.at(indLast) - ps.at(indFirst-1);

        Model::PointVector res(ps.count() - (indLast-indFirst+1));

        std::copy(ps.begin(), ps.begin()+indFirst, res.begin());
        std::transform(ps.begin()+indLast+1,
                       ps.end(),
                       res.begin()+indFirst,
                       [delta](double p) {return p-delta;} );

        setPoints(row, res);
    });
}

void TraceView::duplicateSelected()
{
    forAffectedRows([this](int row) {
        int indFirst = selectionMinIndex(row);
        if (indFirst <= 0)
            return;

        int indLast = selectionMaxIndex(row);
        Model::PointVector ps = points(row);

        if (indLast >= ps.count())
            return;

        double delta = ps.at(indLast) - ps.at(indFirst-1);

        Model::PointVector res(ps.count() + (indLast-indFirst+1));

        std::copy(ps.begin(), ps.begin()+indLast+1, res.begin());
        std::transform(ps.begin()+indFirst,
                       ps.end(),
                       res.begin()+indLast+1,
                       [delta](double p) {return p+delta;} );

        setPoints(row, res);
    });
}

void TraceView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    setCurrent(current, true);
    setCurrent(previous, false);

    updateScrollBars();
    updateAxes();
}

void TraceView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                            const QVector<int> &roles)
{
    QAbstractItemView::dataChanged(topLeft, bottomRight, roles);    

    int rCol = bottomRight.column();
    int lCol = topLeft.column();
    bool notAffected
            = (m_pointsColumn > rCol || m_pointsColumn < lCol)
            && (m_sampleSpacingColumn > rCol || m_sampleSpacingColumn < lCol);

    if (notAffected)
        return;    

    for (int row = topLeft.row(); row <= bottomRight.row(); ++row)
        m_chart->updateSeries(row, points(row), sampleSpacing(row));

    updateScrollBars();
    updateAxes();
}

void TraceView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent)    

    for (int row = start; row <= end; ++row) {
        m_chart->addSeries(row, points(row), sampleSpacing(row));        
        m_chart->setSeriesVisible(row, m_useAll);
    }

    updateScrollBars();
    updateAxes();

    QAbstractItemView::rowsInserted(parent, start, end);
}

void TraceView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent)

    for (int row = start; row <= end; ++row)
        m_chart->removeSeries(row);

    updateScrollBars();
    updateAxes();

    QAbstractItemView::rowsAboutToBeRemoved(parent, start, end);
}

void TraceView::updateScrollBars()
{
    QRectF seriesRect = m_chart->visibleSeriesValueRect();
    QPointF seriesTopLeft = m_chart->mapToPosition(seriesRect.bottomLeft());
    QPointF seriesBottomRight = m_chart->mapToPosition(seriesRect.topRight());

    const QValueAxis *axisX = m_chart->valueAxisX();
    const QValueAxis *axisY = m_chart->valueAxisY();
    QPointF axesTopLeft = m_chart->mapToPosition(QPointF(axisX->min(),
                                                         axisY->max()) );

    QPointF axesBottomRight = m_chart->mapToPosition(QPointF(axisX->max(),
                                                             axisY->min()) );

    setupScrollBar(horizontalScrollBar(),
                   axesTopLeft.x(), axesBottomRight.x(),
                   seriesTopLeft.x(), seriesBottomRight.x());

    setupScrollBar(verticalScrollBar(),
                   axesTopLeft.y(), axesBottomRight.y(),
                   seriesTopLeft.y(), seriesBottomRight.y());
}

void TraceView::updateVisability()
{
    if (m_useAll) {
        m_chart->setSeriesVisible(true);
    }
    else {
        //todo exactly fill indicies by range v3
        m_chart->setSeriesVisible(false);

        int row = currentIndex().row();
        if (row != -1)
            m_chart->setSeriesVisible(row, true);
    }

    updateScrollBars();
}

void TraceView::setResolution(double resolution, double oldResolution,
                              QValueAxis *axis, const QByteArray &signal)
{
    if (resolution == oldResolution)
        return;

    double axisPage = axis->max() - axis->min();
    double newAxisMax = axis->min() + axisPage * oldResolution / resolution;
    axis->setMax(newAxisMax);

    updateScrollBars();

    staticMetaObject.invokeMethod(this, signal, Q_ARG(double, resolution));
}

void TraceView::emitResolutionsChanged()
{
    emit horizontalResolutionChanged(horizontalResolution());
    emit verticalResolutionChanged(verticalResolution());
}

void TraceView::setCurrent(const QModelIndex &index, bool current)
{
    if (!index.isValid())
        return;

    m_chart->highlightSeries(index.row(), current);
    if (!m_useAll)
        m_chart->setSeriesVisible(index.row(), current);
}

int TraceView::selectionMinIndex(int row) const
{
    double min = m_chart->selection()->min();
    return std::lround(std::ceil(min / sampleSpacing(row)));
}

int TraceView::selectionMaxIndex(int row) const
{
    double max = m_chart->selection()->max();
    return std::lround(std::floor(max / sampleSpacing(row)));
}

void TraceView::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dx);
    Q_UNUSED(dy);

    updateAxes();
}

QModelIndex TraceView::moveCursor(CursorAction cursorAction,
                                  Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(cursorAction)
    Q_UNUSED(modifiers)

    //todo implement: move if in trace selection mode

    return currentIndex();
}

int TraceView::horizontalOffset() const
{
    //todo implement
    return 0;
}

int TraceView::verticalOffset() const
{
    //todo implement
    return 0;
}

bool TraceView::isIndexHidden(const QModelIndex &index) const
{
    return index.column() != m_pointsColumn;
}

void TraceView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    Q_UNUSED(rect)
    Q_UNUSED(command)

    //todo implement: select if in trace selection mode
}

QRegion TraceView::visualRegionForSelection(const QItemSelection &selection) const
{
    Q_UNUSED(selection)

    //todo implement: select if in trace selection mode

    return QRegion();
}

void TraceView::resizeEvent(QResizeEvent *)
{
    emitResolutionsChanged();
}

void TraceView::showEvent(QShowEvent *)
{
    emitResolutionsChanged();
}

Model::PointVector TraceView::points(int row) const
{
    return value<Model::PointVector>(row, m_pointsColumn);
}

void TraceView::setPoints(int row, const Model::PointVector &points)
{
    QAbstractItemModel *model = this->model();

    Q_CHECK_PTR(model);
    Q_ASSERT(row>=0 && row<model->rowCount());

    QModelIndex index = model->index(row, m_pointsColumn);
    model->setData(index, QVariant::fromValue(points));
}

/*!
 * \brief TraceView::sampleSpacing
 * \param row
 * \return sample spacing in meters
 */
double TraceView::sampleSpacing(int row) const
{
    return value<double>(row, m_sampleSpacingColumn);
}

void TraceView::updateAxes()
{
    setupAxis(m_chart->valueAxisX(), horizontalScrollBar(),
              m_chart->visibleSeriesMinX(), m_chart->visibleSeriesMaxX() );

    setupAxis(m_chart->valueAxisY(), verticalScrollBar(),
              m_chart->visibleSeriesMinY(), m_chart->visibleSeriesMaxY() );

    emitResolutionsChanged();
}

void TraceView::setupScrollBar(QScrollBar *bar,
                               double axisMin, double axisMax,
                               double seriesMin, double seriesMax)
{
    using std::lround;    

    double axisPage = axisMax-axisMin;
    bar->setPageStep(lround(axisPage));
    bar->setRange(lround(seriesMin), lround(seriesMax-axisPage));
    bar->setValue(lround(axisMin));
}

void TraceView::setupAxis(QValueAxis *axis, const QScrollBar *bar,
                          double seriesMin, double seriesMax)
{
    double axisPage = axis->max() - axis->min();
    double seriesWidth = seriesMax - seriesMin;
    int barWidth = bar->maximum() - bar->minimum();

    double newAxisMin;
    if (barWidth>0) {
        double barRatio = double(bar->value() - bar->minimum()) / barWidth;
        newAxisMin = seriesMin + barRatio * (seriesWidth - axisPage);
    }
    else {
//        newAxisMin = seriesMin - (axisPage - seriesWidth)/2;
        newAxisMin = axis->min();
    }

    axis->setRange(newAxisMin, newAxisMin + axisPage);
}

double TraceView::resolution(double plotLength, const QValueAxis *axis)
{
    return plotLength/(axis->max() - axis->min());
}

bool TraceView::useAll() const
{
    return m_useAll;
}

void TraceView::setUseAll(bool useAll)
{
    if (m_useAll == useAll)
        return;

    m_useAll = useAll;
    updateVisability();
    emit useAllToggled(m_useAll);
}

template<class T>
T TraceView::value(int row, int column) const
{
    QAbstractItemModel *model = this->model();

    Q_CHECK_PTR(model);
    Q_ASSERT(row>=0 && row<model->rowCount());

    QModelIndex index = model->index(row, column);
    return model->data(index).value<T>();
}

template<class Op>
void TraceView::forAffectedRows(Op op) const
{
    if (m_useAll) {
        for (int row = 0; row < model()->rowCount(); ++row)
            op(row);
    }
    else {
        int row = currentIndex().row();
        if (row != -1)
            op(row);
    }
}

const int TraceView::m_pointsColumn = int(Model::ReflectogramColumn::Points);
const int TraceView::m_sampleSpacingColumn = int(Model::ReflectogramColumn::SampleSpacingMeter);
