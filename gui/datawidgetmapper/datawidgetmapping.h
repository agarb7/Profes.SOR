#ifndef DATAWIDGETMAPPING_H
#define DATAWIDGETMAPPING_H

#include <QWidget>
#include <QMetaProperty>
#include <QMetaMethod>

class DataWidgetMapper;

class DataWidgetMapping : public QObject
{
    Q_OBJECT
public:
    explicit DataWidgetMapping(int section,
                               QWidget *widget,
                               QMetaProperty property,
                               DataWidgetMapper *parent = 0);

    static const QMetaMethod modelDataSetter;
    static const QMetaMethod widgetDataSetter;

    int section() const;

    QWidget *widget() const;

    QMetaProperty property() const;

public slots:
    void setModelData();
    void setWidgetData();

private:
    DataWidgetMapper *mapper() const;

    static QMetaMethod method(const char* signature);

    int m_section;
    QWidget *m_widget;
    QMetaProperty m_property;

    bool m_ignored = false;
};

#endif // DATAWIDGETMAPPING_H
