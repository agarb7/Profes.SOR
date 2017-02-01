#ifndef INTCOLUMN_H
#define INTCOLUMN_H

#include "typedcolumn.h"

namespace Model {

template <Core::Reflectogram::Field field>
class IntColumn: public TypedColumn<int, field>
{
public:
    using TypedColumn<int, field>::TypedColumn;

protected:
    using typename TypedColumn<int, field>::CoreValueType;

    virtual CoreValueType toCoreValue(const int &modelValue,
                                      const Core::Reflectogram &) const
    {
        return modelValue;
    }

    virtual int toModelValue(const CoreValueType &coreValue,
                             const Core::Reflectogram &) const
    {
        return coreValue;
    }
};

} // namespace Model

#endif // INTCOLUMN_H
