#ifndef MODELSECTIONOBJECT_H
#define MODELSECTIONOBJECT_H

#include <QObject>
#include <QMetaProperty>

namespace Utils {

class DataPropertyMapper;

namespace Detail {

class ModelSectionObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)

public:
    explicit ModelSectionObject(int section,
                                DataPropertyMapper *parent);

    QVariant data() const;
    void setData(const QVariant &data);

    static const QMetaProperty dataProperty;

signals:
    void dataChanged();

public slots:
    void onModelDataChanged();

private:
    DataPropertyMapper *mapper() const;

    int m_section;
};

} } // namespace Utils::Detail

#endif // MODELSECTIONOBJECT_H
