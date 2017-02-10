#include "datawidgetmapping.h"

#include "datawidgetmapper.h"

DataWidgetMapping::DataWidgetMapping(int section,
                                     QWidget *widget,
                                     QMetaProperty property,
                                     DataWidgetMapper *parent) :
    QObject(parent),
    m_section(section),
    m_widget(widget),
    m_property(property)
{
}

const QMetaMethod DataWidgetMapping::modelDataSetter
    = DataWidgetMapping::method("setModelData()");

const QMetaMethod DataWidgetMapping::widgetDataSetter
    = DataWidgetMapping::method("setWidgetData()");

int DataWidgetMapping::section() const
{
    return m_section;
}

QWidget *DataWidgetMapping::widget() const
{
    return m_widget;
}

QMetaProperty DataWidgetMapping::property() const
{
    return m_property;
}

void DataWidgetMapping::setModelData()
{
    if (m_ignored)
        return;

    m_ignored = true;

    DataWidgetMapper *mapper = this->mapper();

    QModelIndex index = mapper->modelIndex(m_section);
    QVariant value = m_property.read(m_widget);
    mapper->model()->setData(index, value);

    m_ignored = false;
}

void DataWidgetMapping::setWidgetData()
{
    if (m_ignored)
        return;

    m_ignored = true;

    DataWidgetMapper *mapper = this->mapper();

    QModelIndex index = mapper->modelIndex(m_section);
    QVariant value = index.data();
    m_property.write(m_widget, value);

    m_ignored = false;
}

DataWidgetMapper *DataWidgetMapping::mapper() const
{
    return static_cast<DataWidgetMapper*>(parent());
}

QMetaMethod DataWidgetMapping::method(const char *signature)
{
    QByteArray normSig = QMetaObject::normalizedSignature(signature);
    int idx = staticMetaObject.indexOfSlot(normSig);

    return staticMetaObject.method(idx);
}
