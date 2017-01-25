#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->fileListPanel->setModel(&model);
    ui->reflectogramWidget->setModel(&model);

    connect(ui->fileListPanel, &FileListPanel::activated,
            ui->reflectogramWidget, &ReflectogramWidget::setCurrentIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}
