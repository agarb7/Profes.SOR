#ifndef STRINGCOLUMN_H
#define STRINGCOLUMN_H

#include "typedcolumn.h"

#include <QString>

namespace Model {

template <Core::Reflectogram::Field field>
class StringColumn: public TypedColumn<QString, field>
{
    using Base = TypedColumn<QString, field>;

public:
    using Base::Base;

protected:
    Core::String toCoreValue(const QString &modelValue, const Core::Reflectogram &) const override
    {
        return modelValue.toStdString();
    }

    QString toModelValue(const Core::String &coreValue, const Core::Reflectogram &) const override
    {
        return QString::fromStdString(coreValue);
    }
};

} // namespace Model

#endif // STRINGCOLUMN_H
