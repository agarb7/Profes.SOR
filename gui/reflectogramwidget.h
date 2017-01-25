#ifndef REFLECTOGRAMWIDGET_H
#define REFLECTOGRAMWIDGET_H

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
    void setupItemModel(ReflectogramModel *model, int section,
                        QWidget *editor, Label *label, ToAllButton *button = 0);

    Ui::ReflectogramWidget *ui;
    QDataWidgetMapper m_mapper;
};

#endif // REFLECTOGRAMWIDGET_H
