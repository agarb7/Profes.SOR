#ifndef SAMPLESPACINGMETERCOLUMN_H
#define SAMPLESPACINGMETERCOLUMN_H

#include "../abstractcolumn.h"

class SampleSpacingMeterColumn: public AbstractColumn
{
public:
    using AbstractColumn::AbstractColumn;

    virtual QVariant data(const Core::Reflectogram &r) const;
    virtual SetResults setData(Core::Reflectogram &, const QVariant &) const;
};

#endif // SAMPLESPACINGMETERCOLUMN_H
