#include "pointscolumn.h"

#include <algorithm>
#include <cmath>

namespace Model {

Core::LeUInt16Vector PointsColumn::toCoreValue(const PointVector &points,
                                               const Core::Reflectogram &r) const
{
    return transform<Core::LeUInt16Vector>(points, [this, &r](double p) {
        return toCorePoint(p,r);
    });
}

PointVector PointsColumn::toModelValue(const Core::LeUInt16Vector &corePoints,
                                       const Core::Reflectogram &r) const
{
    return transform<PointVector>(corePoints, [this, &r](Core::LeUInt16 p) {
        return toModelPoint(p,r);
    });
}

template <class To, class From, class Op>
To PointsColumn::transform(const From& from, Op op)
{
    int count = from.size();
    To to(count);

    std::transform(from.begin(), from.end(), to.begin(), op);

    return to;
}

double PointsColumn::factor(const Core::Reflectogram &r)
{
    double k = r.value<Core::Reflectogram::ScalingFactor>();
    return -k/1000000;
}

Core::LeUInt16 PointsColumn::toCorePoint(double modelPoint, const Core::Reflectogram &r)
{
    return std::lround( modelPoint/factor(r) );
}

double PointsColumn::toModelPoint(Core::LeUInt16 corePoint, const Core::Reflectogram &r)
{
    return corePoint * factor(r);
}

} // namespace Model
