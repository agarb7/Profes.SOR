#ifndef TIMETOALLBUTTON_H
#define TIMETOALLBUTTON_H

#include "toallbutton.h"
#include "timetoalldialog.h"

#include <QDateTime>

class ReflectogramWidget;

class TimeToAllButton : public ToAllButton
{
    Q_OBJECT

public:
    explicit TimeToAllButton(QWidget *parent = 0);

    ReflectogramWidget *reflectogramWidget() const;
    void setReflectogramWidget(ReflectogramWidget *reflectogramWidget);

protected:
    void onClick() override;

private:
    bool reflectogramWidgetCurrentIndexIsValid();

    QDate date(int row) const;
    void setDateTime(int row, const QDateTime &date);

    int randomStep() const;

    TimeToAllDialog m_dialog;
    ReflectogramWidget *m_reflectogramWidget = 0;
};

#endif // TIMETOALLBUTTON_H
