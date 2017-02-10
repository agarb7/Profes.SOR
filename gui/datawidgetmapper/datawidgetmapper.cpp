#include "datawidgetmapper.h"

#include "datawidgetmapping.h"
#include "sectionobject.h"

#include <algorithm>

DataWidgetMapper::DataWidgetMapper(QObject *parent)
    : QObject(parent)
{
}

QAbstractItemModel *DataWidgetMapper::model() const
{
    return m_model;
}

void DataWidgetMapper::setModel(QAbstractItemModel *model)
{
    m_model = model;

    auto onDataChanged = [this](const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        if (m_currentIndex < index(topLeft) || m_currentIndex > index(bottomRight))
            return;

        for (int sect = section(topLeft), last = section(bottomRight);
             sect <= last; ++sect)
        {
            auto sectObj = sectionObject(sect, false);
            if (!sectObj)
                continue;

            sectObj->emitDataChanged();
        }
    };

    connect(m_model, &QAbstractItemModel::dataChanged, onDataChanged);
}

int DataWidgetMapper::currentIndex() const
{
    return m_currentIndex;
}

void DataWidgetMapper::setCurrentIndex(int currentIndex)
{
    m_currentIndex = currentIndex;

    for (auto obj: m_sectionObjects)
        obj->emitDataChanged();

    emit currentIndexChanged(m_currentIndex);
}

QModelIndex DataWidgetMapper::modelIndex(int section) const
{
    return modelIndex(m_currentIndex, section);
}

void DataWidgetMapper::addToWidgetMapping(int section,
                                          QWidget *widget,
                                          QMetaProperty property)
{    
    auto mapping = this->mapping(section, widget, property);
    addToWidgetMappingImpl(mapping);
}

/*!
 * \brief DataWidgetMapper::addToModelMapping
 * \param widget
 * \param property must has notify signal
 * \param section 
 */
void DataWidgetMapper::addToModelMapping(int section,
                                         QWidget *widget,
                                         QMetaProperty property)
{
    auto mapping = this->mapping(section, widget, property);
    addToModelMappingImpl(mapping);
}

void DataWidgetMapper::addMapping(int section,
                                  QWidget *widget,
                                  QMetaProperty property)
{
    auto mapping = this->mapping(section, widget, property);

    addToWidgetMappingImpl(mapping);
    addToModelMappingImpl(mapping);
}

void DataWidgetMapper::addToWidgetMappingImpl(DataWidgetMapping *mapping)
{
    auto sectionObj = this->sectionObject(mapping->section(),
                                          true);

    connect(sectionObj, SIGNAL(dataChanged()),
            mapping, SLOT(setWidgetData()),
            m_connectionType);
}

void DataWidgetMapper::addToModelMappingImpl(DataWidgetMapping *mapping)
{
    connect(mapping->widget(), mapping->property().notifySignal(),
            mapping, DataWidgetMapping::modelDataSetter,
            m_connectionType);
}

DataWidgetMapping *DataWidgetMapper::mapping(int section,
                                             QWidget *widget,
                                             QMetaProperty property)
{
    MappingKey key = qMakePair(section,
                               qMakePair(widget, property.propertyIndex()));

    DataWidgetMapping *&mapping = m_mappingHash[key];
    if (!mapping)
        mapping = new DataWidgetMapping(section, widget, property, this);

    return mapping;
}

SectionObject *DataWidgetMapper::sectionObject(int section, bool canCreate)
{
    SectionObject *sectObj = m_sectionObjects.value(section);
    if (sectObj)
        return sectObj;

    if (canCreate)
        return m_sectionObjects[section] = new SectionObject(this);

    return 0;
}

int DataWidgetMapper::index(const QModelIndex &idx) const
{
    return m_orientation == Qt::Horizontal
            ? idx.row()
            : idx.column();
}

int DataWidgetMapper::section(const QModelIndex &idx) const
{
    return m_orientation == Qt::Horizontal
            ? idx.column()
            : idx.row();
}

QModelIndex DataWidgetMapper::modelIndex(int index, int section) const
{
    if (!m_model)
        return QModelIndex();

    if (m_orientation == Qt::Vertical)
        std::swap(index, section);

    return m_model->index(index, section);
}

QMetaProperty DataWidgetMapper::userProperty(const QWidget *widget) const
{
    return widget->metaObject()->userProperty();
}

QMetaProperty DataWidgetMapper::property(const QWidget *widget,
                                         const char *name) const
{
    const QMetaObject *metaObj = widget->metaObject();
    int propIdx = metaObj->indexOfProperty(name);

    return metaObj->property(propIdx);
}
