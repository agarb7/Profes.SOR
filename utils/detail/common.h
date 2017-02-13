#ifndef COMMON_H
#define COMMON_H

#include <QMetaProperty>
#include <QByteArray>

namespace Utils { namespace Detail {

QMetaProperty userProperty(const QObject *object);
QMetaProperty property(const QObject *object, const QByteArray &name);

} } // namespace Utils::Detail

#endif // COMMON_H
