#ifndef INTCOLUMN_H
#define INTCOLUMN_H

#include "typedcolumn.h"

template <Core::Reflectogram::Field field>
class IntColumn: public TypedColumn<int, field>
{
public:
    using TypedColumn<int, field>::TypedColumn;

protected:
    using typename TypedColumn<int, field>::CoreValueType;

    virtual CoreValueType toCoreValue(const int &modelValue) const
    {
        return modelValue;
    }

    virtual int toModelValue(const CoreValueType &coreValue) const
    {
        return coreValue;
    }
};

#endif // INTCOLUMN_H
