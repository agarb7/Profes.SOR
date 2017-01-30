#include "samplespacingmetercolumn.h"

#include "core/reflectogram.h"

QVariant SampleSpacingMeterColumn::data(const Core::Reflectogram &r) const
{
    const long double sol = 299.792458;

    long double ss = r.value<Core::Reflectogram::SampleSpacing>();
    long double ior = r.value<Core::Reflectogram::IndexOfRefraction>();
    long double result = ss * sol / (ior * 1000);

    return double(result);
}

AbstractColumn::SetResults
SampleSpacingMeterColumn::setData(Core::Reflectogram &, const QVariant &) const
{
    return NotAccepted;
}
