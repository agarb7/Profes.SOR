#ifndef SECTIONOBJECT_H
#define SECTIONOBJECT_H

#include <QObject>

class SectionObject : public QObject
{
    Q_OBJECT
public:
    explicit SectionObject(QObject *parent = 0);

    void emitDataChanged();

signals:
    void dataChanged();
};

#endif // SECTIONOBJECT_H
