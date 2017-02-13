#include "modelsectionobject.h"

#include "../datapropertymapper.h"

#include <QAbstractItemModel>

namespace Utils { namespace Detail {

ModelSectionObject::ModelSectionObject(int section,
                                       DataPropertyMapper *parent) :
    QObject(parent),
    m_section(section)
{
    Q_CHECK_PTR(parent);
}

QVariant ModelSectionObject::data() const
{
    Q_CHECK_PTR(mapper()->model());

    return mapper()
            ->currentModelIndex(m_section)
            .data();
}

void ModelSectionObject::setData(const QVariant &data)
{
    Q_CHECK_PTR(mapper()->model());

    QModelIndex index = mapper()->currentModelIndex(m_section);

    mapper()->model()->setData(index, data);
}

const QMetaProperty ModelSectionObject::dataProperty
    = ModelSectionObject::staticMetaObject.property(
        ModelSectionObject::staticMetaObject.indexOfProperty("data")
    );

/*!
 * \brief ModelSectionObject::onModelDataChanged
 * must be trigger of parent DataPropertyMapper every time when it's model data changed in m_section
 */
void ModelSectionObject::onModelDataChanged()
{
    emit dataChanged();
}

DataPropertyMapper *ModelSectionObject::mapper() const
{
    return static_cast<DataPropertyMapper*>(parent());
}

} } // namespace Utils::Detail
