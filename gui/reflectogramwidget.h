#ifndef REFLECTOGRAMWIDGET_H
#define REFLECTOGRAMWIDGET_H

#include "model/reflectogrammodelcolumn.h"

#include <QWidget>
#include <QDataWidgetMapper>

class ReflectogramModel;
class ToAllButton;
class Label;

namespace Ui {
class ReflectogramWidget;
}

class ReflectogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReflectogramWidget(QWidget *parent = 0);
    ~ReflectogramWidget();

    ReflectogramModel *model() const;
    void setModel(ReflectogramModel *model);

public slots:
    void setCurrentIndex(int index);    

private:
    void setupItemModel(ReflectogramModel *model, ReflectogramModelColumn columnId,
                        QWidget *editor, Label *label = 0, ToAllButton *button = 0);

    Ui::ReflectogramWidget *ui;
    QDataWidgetMapper m_mapper;
};

#endif // REFLECTOGRAMWIDGET_H
