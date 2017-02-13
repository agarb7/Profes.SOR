#ifndef DATAPROPERTYMAPPER_H
#define DATAPROPERTYMAPPER_H

#include <QAbstractItemModel>
#include <QFlags>
#include <QHash>
#include <QVector>
#include <QByteArray>

namespace Utils {

class ObjectPropertyMapping;

namespace Detail {

class ModelSectionObject;

}

/*!
 * \brief The DataPropertyMapper class
 *
 * Only same thread connection allowed.
 * Allow dyn change orientation and model, mapping will not removing (todo: ensure this)
 */
class DataPropertyMapper : public QObject
{
    Q_OBJECT
public:
    enum MappingDirection {
        ToWidgetMapping = 1,
        ToModelMapping = 2,
        BothMapping = 3
    };

    Q_DECLARE_FLAGS(MappingDirections, MappingDirection)

    explicit DataPropertyMapper(QObject *parent = 0);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    void addMapping(int section,
                    QObject *object,
                    QMetaProperty property,
                    MappingDirections directions = BothMapping);

    void addMapping(int section,
                    QObject *object,
                    const QByteArray &propertyName,
                    MappingDirections directions = BothMapping);

    void addMapping(int section,
                    QObject *object,
                    MappingDirections directions = BothMapping);

    int currentIndex() const;
    void setCurrentIndex(int currentIndex);
    bool isCurrentIndexValid() const;
    QModelIndex currentModelIndex(int section) const;

signals:
    void currentIndexChanged(int index);

private slots:
    void onModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    int index(const QModelIndex &idx) const;
    int indexCount() const;
    int section(const QModelIndex &idx) const;
    QModelIndex modelIndex(int index, int section) const;

    QAbstractItemModel *m_model = 0;
    int m_currentIndex = -1;

    Qt::Orientation m_orientation = Qt::Horizontal;

    QHash<int, Detail::ModelSectionObject*> m_sectionObjects;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DataPropertyMapper::MappingDirections)

} // namespace Utils

#endif // DATAPROPERTYMAPPER_H
