#ifndef OBJECTPROPERTYMAPPING_H
#define OBJECTPROPERTYMAPPING_H

#include <QObject>
#include <QMetaProperty>
#include <QMetaMethod>
#include <QByteArray>
#include <QFlags>

namespace Utils {

/*!
 * \brief The ObjectPropertyMapping class
 * Only same thread connection allowed
 */
class ObjectPropertyMapping : public QObject
{
    Q_OBJECT
public:
    enum MappingDirection {
        ToSecondMapping = 1,
        ToFirstMapping = 2,
        BothMapping = 3
    };

    Q_DECLARE_FLAGS(MappingDirections, MappingDirection)

    ObjectPropertyMapping(QObject *firstObject, QMetaProperty firstProperty,
                          QObject *secondObject, QMetaProperty secondProperty,
                          MappingDirections directions = BothMapping, QObject *parent = 0);

    ObjectPropertyMapping(QObject *firstObject, const QByteArray &firstProperty,
                          QObject *secondObject, const QByteArray &secondProperty,
                          MappingDirections directions = BothMapping, QObject *parent = 0);

public slots:
    void writeSecondProperty();
    void writeFirstProperty();

private:
    struct ObjectProperty {
        QObject *object;
        QMetaProperty property;
    };

    void writeProperty(const ObjectProperty &from, ObjectProperty &to);

    static QMetaMethod method(const char *signature);

    ObjectProperty m_first;
    ObjectProperty m_second;

    bool m_ignored = false;

    static const QMetaMethod m_secondPropertyWriter;
    static const QMetaMethod m_firstPropertyWriter;

    static const Qt::ConnectionType m_connectionType
        = Qt::ConnectionType(Qt::DirectConnection | Qt::UniqueConnection);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ObjectPropertyMapping::MappingDirections)

} // namespace Utils

#endif // OBJECTPROPERTYMAPPING_H
