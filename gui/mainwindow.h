#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model/reflectogram_.h"

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Model::Reflectogram model;
};

#endif // MAINWINDOW_H
