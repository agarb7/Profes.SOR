#include "sectionobject.h"

SectionObject::SectionObject(QObject *parent) : QObject(parent)
{
}

void SectionObject::emitDataChanged()
{
    emit dataChanged();
}
