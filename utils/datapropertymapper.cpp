#include "datapropertymapper.h"

#include "detail/modelsectionobject.h"
#include "detail/common.h"

#include "objectpropertymapping.h"

#include <utility>

namespace Utils {

DataPropertyMapper::DataPropertyMapper(QObject *parent) :
    QObject(parent)
{
}

QAbstractItemModel *DataPropertyMapper::model() const
{
    return m_model;
}

void DataPropertyMapper::setModel(QAbstractItemModel *model)
{
    if (m_model) {
        disconnect(m_model,
                   &QAbstractItemModel::dataChanged,
                   this,
                   &DataPropertyMapper::onModelDataChanged);
    }

    m_model = model;

    connect(m_model,
            &QAbstractItemModel::dataChanged,
            this,
            &DataPropertyMapper::onModelDataChanged);
}

/*!
 * \brief DataPropertyMapper::addMapping
 * Duplicate mapping is not checked
 * \param section
 * \param object
 * \param property
 * \param directions
 */
void DataPropertyMapper::addMapping(int section,
                                    QObject *object,
                                    QMetaProperty property,
                                    MappingDirections directions)
{
    Q_ASSERT(int(ToWidgetMapping) == int(ObjectPropertyMapping::ToSecondMapping));
    Q_ASSERT(int(ToModelMapping) == int(ObjectPropertyMapping::ToFirstMapping));
    Q_ASSERT(int(BothMapping) == int(ObjectPropertyMapping::BothMapping));

    Detail::ModelSectionObject *&sectObj = m_sectionObjects[section];
    if (!sectObj)
        sectObj = new Detail::ModelSectionObject(section, this);

    new ObjectPropertyMapping(sectObj,
                              Detail::ModelSectionObject::dataProperty,
                              object,
                              property,
                              ObjectPropertyMapping::MappingDirections(int(directions)),
                              this);
}

void DataPropertyMapper::addMapping(int section,
                                    QObject *object,
                                    const QByteArray &propertyName,
                                    MappingDirections directions)
{
    addMapping(section,
               object,
               Detail::property(object, propertyName),
               directions);
}

void DataPropertyMapper::addMapping(int section,
                                    QObject *object,
                                    MappingDirections directions)
{
    addMapping(section,
               object,
               Detail::userProperty(object),
               directions);
}

int DataPropertyMapper::currentIndex() const
{
    return m_currentIndex;
}

void DataPropertyMapper::setCurrentIndex(int currentIndex)
{
    if (m_currentIndex == currentIndex)
        return;

    m_currentIndex = currentIndex;

    for (auto sectObj: m_sectionObjects)
        sectObj->onModelDataChanged();

    emit currentIndexChanged(m_currentIndex);
}

bool DataPropertyMapper::isCurrentIndexValid() const
{
    return m_model
            && m_currentIndex >= 0
            && m_currentIndex < indexCount();
}

QModelIndex DataPropertyMapper::currentModelIndex(int section) const
{
    return modelIndex(m_currentIndex, section);
}

void DataPropertyMapper::onModelDataChanged(const QModelIndex &topLeft,
                                            const QModelIndex &bottomRight)
{
    if (m_currentIndex < index(topLeft) || m_currentIndex > index(bottomRight))
        return;

    for (int sect = section(topLeft), last = section(bottomRight);
         sect <= last; ++sect)
    {
        Detail::ModelSectionObject *sectObj = m_sectionObjects.value(sect);
        if (!sectObj)
            continue;

        sectObj->onModelDataChanged();
    }
}

int DataPropertyMapper::index(const QModelIndex &idx) const
{
    return m_orientation == Qt::Horizontal
            ? idx.row()
            : idx.column();
}

/*!
 * \brief DataPropertyMapper::indexCount
 * Model must be setup
 * \return
 */
int DataPropertyMapper::indexCount() const
{
    Q_CHECK_PTR(m_model);

    return m_orientation == Qt::Horizontal
            ? m_model->rowCount()
            : m_model->columnCount();
}

int DataPropertyMapper::section(const QModelIndex &idx) const
{
    return m_orientation == Qt::Horizontal
            ? idx.column()
            : idx.row();
}

/*!
 * \brief DataPropertyMapper::modelIndex
 * \param index
 * \param section
 * Model must be setup
 * \return
 */
QModelIndex DataPropertyMapper::modelIndex(int index, int section) const
{
    Q_CHECK_PTR(m_model);

    if (m_orientation == Qt::Vertical)
        std::swap(index, section);

    return m_model->index(index, section);
}

} // namespace Utils
