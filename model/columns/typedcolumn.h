#ifndef TYPEDCOLUMN_H
#define TYPEDCOLUMN_H

#include "../abstractcolumn.h"

#include "core/reflectogram.h"

template <class ModelValueType_, Core::Reflectogram::Field field>
class TypedColumn : public AbstractColumn
{
protected:
    using CoreValueType = Core::Reflectogram::ValueType<field>;
    using ModelValueType = ModelValueType_;

public:
    using AbstractColumn::AbstractColumn;

    virtual QVariant data(const Core::Reflectogram &r) const
    {
        return QVariant::fromValue(
                    toModelValue(r.value<field>()) );
    }

    virtual SetResults setData(Core::Reflectogram &r, const QVariant &value) const
    {
        if (r.empty() || !value.canConvert<ModelValueType>())
            return NotAccepted;

        CoreValueType newValue = toCoreValue(value.value<ModelValueType>());
        if (r.value<field>() != newValue) {
            r.setValue<field>(newValue);
            return Accepted|Changed;
        }

        return Accepted;
    }

protected:
    virtual CoreValueType toCoreValue(const ModelValueType &modelValue) const = 0;
    virtual ModelValueType toModelValue(const CoreValueType &coreValue) const = 0;
};

#endif // TYPEDCOLUMN_H
