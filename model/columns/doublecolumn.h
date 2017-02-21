#ifndef DOUBLECOLUMN_H
#define DOUBLECOLUMN_H

#include "typedcolumn.h"

#include <cmath>

namespace Model {

template <Core::Reflectogram::Field field>
class DoubleColumn: public TypedColumn<double, field>
{
    using Base = TypedColumn<double, field>;
    using typename Base::CoreValueType;

public:
    DoubleColumn (const QString &header, int factor) :
        Base(header),
        m_factor(factor)
    {}

protected:
    CoreValueType toCoreValue(const double &modelValue,
                              const Core::Reflectogram &) const override
    {
        return lround(modelValue * m_factor);
    }

    double toModelValue(const CoreValueType &coreValue,
                        const Core::Reflectogram &) const override
    {
        return double(coreValue) / m_factor;
    }

private:
    int m_factor=0;
};

} // namespace Model

#endif // DOUBLECOLUMN_H
