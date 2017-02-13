#ifndef REFLECTOGRAMWIDGET_H
#define REFLECTOGRAMWIDGET_H

#include "model/reflectogramcolumn.h"

#include "utils/datapropertymapper.h"

#include <QWidget>

class ToAllButton;
class Label;

namespace Model {
    class Reflectogram;
}

namespace Ui {
class ReflectogramWidget;
}

class ReflectogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReflectogramWidget(QWidget *parent = 0);
    ~ReflectogramWidget();

    Model::Reflectogram *model() const;
    void setModel(Model::Reflectogram *model);

public slots:
    void setCurrentIndex(int index);

private:
    void setupItemModel(Model::Reflectogram *model, Model::ReflectogramColumn columnId,
                        QWidget *editor, Label *label = 0, ToAllButton *button = 0);

    void setupTraceEditModel(Model::Reflectogram */*model*/);

    Ui::ReflectogramWidget *ui;
    Utils::DataPropertyMapper m_mapper;
};

#endif // REFLECTOGRAMWIDGET_H
