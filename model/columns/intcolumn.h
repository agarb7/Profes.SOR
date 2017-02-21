#ifndef INTCOLUMN_H
#define INTCOLUMN_H

#include "typedcolumn.h"

namespace Model {

template <Core::Reflectogram::Field field>
class IntColumn: public TypedColumn<int, field>
{
    using Base = TypedColumn<int, field>;
    using typename Base::CoreValueType;

public:
    using Base::Base;

protected:
    CoreValueType toCoreValue(const int &modelValue, const Core::Reflectogram &) const override
    {
        return modelValue;
    }

    int toModelValue(const CoreValueType &coreValue, const Core::Reflectogram &) const override
    {
        return coreValue;
    }
};

} // namespace Model

#endif // INTCOLUMN_H
