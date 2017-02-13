#include "objectpropertymapping.h"

#include "detail/common.h"

#include <QVariant>

namespace Utils {

ObjectPropertyMapping::ObjectPropertyMapping(QObject *firstObject, QMetaProperty firstProperty,
                                             QObject *secondObject, QMetaProperty secondProperty,
                                             MappingDirections directions, QObject *parent) :
    QObject(parent),
    m_first{firstObject, firstProperty},
    m_second{secondObject, secondProperty}
{
    if (directions.testFlag(ToSecondMapping)) {
        connect(firstObject,
                firstProperty.notifySignal(),
                this,
                m_secondPropertyWriter,
                m_connectionType);
    }

    if (directions.testFlag(ToFirstMapping)) {
        connect(secondObject,
                secondProperty.notifySignal(),
                this,
                m_firstPropertyWriter,
                m_connectionType);
    }
}

ObjectPropertyMapping::ObjectPropertyMapping(QObject *firstObject, const QByteArray &firstProperty,
                                             QObject *secondObject, const QByteArray &secondProperty,
                                             MappingDirections directions, QObject *parent) :
    ObjectPropertyMapping(firstObject, Detail::property(firstObject, firstProperty),
                          secondObject, Detail::property(secondObject, secondProperty),
                          directions, parent)
{
}

void ObjectPropertyMapping::writeSecondProperty()
{
    writeProperty(m_first, m_second);
}

void ObjectPropertyMapping::writeFirstProperty()
{
    writeProperty(m_second, m_first);
}

void ObjectPropertyMapping::writeProperty(const ObjectProperty &from,
                                          ObjectProperty &to)
{
    if (m_ignored)
        return;

    m_ignored = true;

    QVariant value = from.property.read(from.object);
    to.property.write(to.object, value);

    m_ignored = false;
}

QMetaMethod ObjectPropertyMapping::method(const char *signature)
{
    QByteArray normSig = QMetaObject::normalizedSignature(signature);
    int idx = staticMetaObject.indexOfSlot(normSig);

    return staticMetaObject.method(idx);
}

const QMetaMethod ObjectPropertyMapping::m_secondPropertyWriter
    = ObjectPropertyMapping::method("writeSecondProperty()");

const QMetaMethod ObjectPropertyMapping::m_firstPropertyWriter
    = ObjectPropertyMapping::method("writeFirstProperty()");

} // namespace Utils
