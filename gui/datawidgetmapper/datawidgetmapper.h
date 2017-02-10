#ifndef DATAWIDGETMAPPER_H
#define DATAWIDGETMAPPER_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QMetaProperty>
#include <QHash>

class DataWidgetMapping;
class SectionObject;

/*!
 * \brief The DataWidgetMapper class
 *
 * Reset model or removing mapping are not supported
 */
class DataWidgetMapper : public QObject
{
    Q_OBJECT
public:
    explicit DataWidgetMapper(QObject *parent = 0);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    int currentIndex() const;
    void setCurrentIndex(int currentIndex);

    QModelIndex modelIndex(int section) const;

    void addToWidgetMapping(int section,
                            QWidget *widget,
                            QMetaProperty property);

    void addToWidgetMapping(int section,
                            QWidget *widget,
                            const char *propertyName)
    {
        addToWidgetMapping(section, widget,
                           property(widget, propertyName));
    }

    void addToWidgetMapping(int section,
                            QWidget *widget)
    {
        addToWidgetMapping(section, widget,
                           userProperty(widget));
    }

    void addToModelMapping(int section,
                           QWidget *widget,
                           QMetaProperty property);

    void addToModelMapping(int section,
                           QWidget *widget,
                           const char *propertyName)
    {
        addToModelMapping(section, widget,
                          property(widget, propertyName));
    }

    void addToModelMapping(int section,
                           QWidget *widget)
    {
        addToModelMapping(section, widget,
                          userProperty(widget));
    }

    void addMapping(int section,
                    QWidget *widget,
                    QMetaProperty property);

    void addMapping(int section,
                    QWidget *widget,
                    const char *propertyName)
    {
        addMapping(section, widget,
                   property(widget, propertyName));
    }

    void addMapping(int section,
                    QWidget *widget)
    {
        addMapping(section, widget,
                   userProperty(widget));
    }

signals:
    void currentIndexChanged(int index);

private:
    using MappingKey = QPair<int, QPair<QWidget*, int>>;
    using MappingHash = QHash<MappingKey, DataWidgetMapping*>;
    using SectionObjectHash = QHash<int, SectionObject*>;

    void addToWidgetMappingImpl(DataWidgetMapping *mapping);

    void addToModelMappingImpl(DataWidgetMapping *mapping);

    DataWidgetMapping *mapping(int section,
                               QWidget *widget,
                               QMetaProperty property);

    SectionObject *sectionObject(int section, bool canCreate);

    int index(const QModelIndex &idx) const;
    int section(const QModelIndex &idx) const;
    QModelIndex modelIndex(int index, int section) const;

    QMetaProperty userProperty(const QWidget *widget) const;
    QMetaProperty property(const QWidget *widget, const char *name) const;

    QAbstractItemModel *m_model = 0;
    int m_currentIndex = -1;

    Qt::Orientation m_orientation = Qt::Horizontal;    

    MappingHash m_mappingHash;
    SectionObjectHash m_sectionObjects;

    static const Qt::ConnectionType m_connectionType
        = Qt::ConnectionType(Qt::DirectConnection | Qt::UniqueConnection);
};

#endif // DATAWIDGETMAPPER_H

