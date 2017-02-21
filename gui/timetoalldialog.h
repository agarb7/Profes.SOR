#ifndef TIMETOALLDIALOG_H
#define TIMETOALLDIALOG_H

#include <QDialog>

namespace Ui {
class TimeToAllDialog;
}

class TimeToAllDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeToAllDialog(QWidget *parent = 0);
    ~TimeToAllDialog();

    int step() const;
    int perturbationRadii() const;

private:
    Ui::TimeToAllDialog *ui;
};

#endif // TIMETOALLDIALOG_H
