#ifndef STRINGCOLUMN_H
#define STRINGCOLUMN_H

#include "typedcolumn.h"

#include <QString>

namespace Model {

template <Core::Reflectogram::Field field>
class StringColumn: public TypedColumn<QString, field>
{
public:
    using TypedColumn<QString, field>::TypedColumn;

protected:
    virtual Core::String toCoreValue(const QString &modelValue, const Core::Reflectogram &) const
    {
        return modelValue.toStdString();
    }

    virtual QString toModelValue(const Core::String &coreValue, const Core::Reflectogram &) const
    {
        return QString::fromStdString(coreValue);
    }
};

} // namespace Model

#endif // STRINGCOLUMN_H
