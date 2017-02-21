#ifndef POINTSCOLUMN_H
#define POINTSCOLUMN_H

#include "typedcolumn.h"
#include "../types_.h"

#include "core/reflectogram.h"

namespace Model {

class PointsColumn: public TypedColumn<PointVector, Core::Reflectogram::Points>
{
    using Base = TypedColumn<PointVector, Core::Reflectogram::Points>;

public:
    using Base::Base;

protected:
    Core::LeUInt16Vector toCoreValue(const PointVector &points,
                                     const Core::Reflectogram &r) const override;

    PointVector toModelValue(const Core::LeUInt16Vector &corePoints,
                             const Core::Reflectogram &r) const override;

private:
    template <class To, class From, class Op>
    static To transform(const From& from, Op op);

    static double factor(const Core::Reflectogram &r);

    static Core::LeUInt16 toCorePoint(double modelPoint, const Core::Reflectogram &r);
    static double toModelPoint(Core::LeUInt16 corePoint, const Core::Reflectogram &r);
};

} // namespace Model

#endif // POINTSCOLUMN_H
