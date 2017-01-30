#ifndef POINTSCOLUMN_H
#define POINTSCOLUMN_H

#include "typedcolumn.h"

#include "core/reflectogram.h"

Q_DECLARE_METATYPE(Core::LeUInt16Vector)

class PointsColumn: public TypedColumn<Core::LeUInt16Vector, Core::Reflectogram::Points>
{
public:
    using TypedColumn::TypedColumn;

protected:
    virtual CoreValueType toCoreValue(const ModelValueType &modelValue) const
    {
        return modelValue;
    }

    virtual ModelValueType toModelValue(const CoreValueType &coreValue) const
    {
        return coreValue;
    }
};

#endif // POINTSCOLUMN_H
