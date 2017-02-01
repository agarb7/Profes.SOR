#ifndef DOUBLECOLUMN_H
#define DOUBLECOLUMN_H

#include "typedcolumn.h"

#include <cmath>

namespace Model {

template <Core::Reflectogram::Field field>
class DoubleColumn: public TypedColumn<double, field>
{
public:
    DoubleColumn (const QString &header, int factor) :
        TypedColumn<double, field>(header),
        m_factor(factor)
    {}

protected:
    using typename TypedColumn<double, field>::CoreValueType;

    virtual CoreValueType toCoreValue(const double &modelValue,
                                      const Core::Reflectogram &) const
    {
        return lround(modelValue * m_factor);
    }

    virtual double toModelValue(const CoreValueType &coreValue,
                                const Core::Reflectogram &) const
    {
        return double(coreValue) / m_factor;
    }

private:
    int m_factor=0;
};

} // namespace Model

#endif // DOUBLECOLUMN_H
