#include "common.h"

namespace Utils { namespace Detail {

QMetaProperty userProperty(const QObject *object)
{
    return object->metaObject()->userProperty();
}

QMetaProperty property(const QObject *object, const QByteArray &name)
{
    const QMetaObject *metaObj = object->metaObject();
    int propIdx = metaObj->indexOfProperty(name);

    return metaObj->property(propIdx);
}

} } // namespace Utils::Detail
