#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model/reflectogrammodel.h"

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

    ReflectogramModel model;
};

#endif // MAINWINDOW_H
