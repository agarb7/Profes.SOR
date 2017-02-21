#include "timetoallbutton.h"

#include "reflectogramwidget.h"

#include "model/reflectogram_.h"
#include "model/reflectogramcolumn.h"

#include <QMessageBox>

#include <random>

TimeToAllButton::TimeToAllButton(QWidget *parent) : ToAllButton(parent)
{    
}

void TimeToAllButton::onClick()
{
    if (!editor() || !reflectogramWidgetCurrentIndexIsValid())
        return;

    QVariant editorData = this->editorData();
    if (!editorData.canConvert<QTime>())
        return;

    if (m_dialog.exec() != QDialog::Accepted)
        return;

    QTime editorTime = editorData.toTime();

    int curIdx = m_reflectogramWidget->currentIndex();
    QDate modelDate = date(curIdx);

    QDateTime curDt(modelDate, editorTime);
    setDateTime(curIdx, curDt);

    QDateTime dt = curDt;
    for (int row = curIdx+1, count = model()->rowCount(); row<count; ++row) {
        dt = dt.addSecs(randomStep());
        setDateTime(row, dt);
    }

    dt = curDt;
    for (int row = curIdx-1; row>=0; --row) {
        dt = dt.addSecs(-randomStep());
        setDateTime(row, dt);
    }

}

bool TimeToAllButton::reflectogramWidgetCurrentIndexIsValid()
{
    if (!m_reflectogramWidget)
        return false;

    int curIdx = m_reflectogramWidget->currentIndex();
    return curIdx >=0 && curIdx < model()->rowCount();
}

QDate TimeToAllButton::date(int row) const
{
    Q_CHECK_PTR(model());
    Q_ASSERT(row >=0 && row < model()->rowCount());

    QModelIndex idx = model()->index(row, int(Model::ReflectogramColumn::Date));
    QVariant data = idx.data();

    Q_ASSERT(data.canConvert<QDate>());

    return data.toDate();
}

//todo: implement this through DateTime column after signals from core will be implemented
void TimeToAllButton::setDateTime(int row, const QDateTime &dateTime)
{
    Q_CHECK_PTR(model());
    Q_ASSERT(row >=0 && row < model()->rowCount());

    Model::Reflectogram *model = this->model();

    QModelIndex dateIdx = model->index(row, int(Model::ReflectogramColumn::Date));
    model->setData(dateIdx, dateTime.date());

    QModelIndex timeIdx = model->index(row, int(Model::ReflectogramColumn::Time));
    model->setData(timeIdx, dateTime.time());
}

int TimeToAllButton::randomStep() const
{
    static std::mt19937 gen((std::random_device())());

    int step = m_dialog.step();
    int rndRadii = m_dialog.perturbationRadii();

    std::uniform_int_distribution<> dis(step-rndRadii, step+rndRadii);

    return dis(gen);
}

ReflectogramWidget *TimeToAllButton::reflectogramWidget() const
{
    return m_reflectogramWidget;
}

void TimeToAllButton::setReflectogramWidget(ReflectogramWidget *reflectogramWidget)
{
    m_reflectogramWidget = reflectogramWidget;
}
