#include "timetoalldialog.h"
#include "ui_timetoalldialog.h"

TimeToAllDialog::TimeToAllDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeToAllDialog)
{
    ui->setupUi(this);

    ui->perturbationRadiiEdit->setMaximum(ui->stepEdit->value());

    connect(ui->stepEdit, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->perturbationRadiiEdit, &QSpinBox::setMaximum);
}

TimeToAllDialog::~TimeToAllDialog()
{
    delete ui;
}

int TimeToAllDialog::step() const
{
    return ui->stepEdit->value();
}

int TimeToAllDialog::perturbationRadii() const
{
    return ui->perturbationRadiiEdit->value();
}
