#ifndef STRINGCOLUMN_H
#define STRINGCOLUMN_H

#include "typedcolumn.h"

#include <QString>

template <Core::Reflectogram::Field field>
class StringColumn: public TypedColumn<QString, field>
{
public:
    using TypedColumn<QString, field>::TypedColumn;

protected:
    virtual Core::String toCoreValue(const QString &modelValue) const
    {
        return modelValue.toStdString();
    }

    virtual QString toModelValue(const Core::String &coreValue) const
    {
        return QString::fromStdString(coreValue);
    }
};

#endif // STRINGCOLUMN_H
