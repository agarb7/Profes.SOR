#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0,0);
    ui->splitter->setStretchFactor(1,1);
    ui->splitter->setSizes({250, 0});

    ui->fileListPanel->setModel(&model);
    ui->reflectogramWidget->setModel(&model);

    connect(ui->fileListPanel, &FileListPanel::activated,
            ui->reflectogramWidget, &ReflectogramWidget::setCurrentIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}
