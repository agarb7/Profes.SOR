#ifndef SAMPLESPACINGMETERCOLUMN_H
#define SAMPLESPACINGMETERCOLUMN_H

#include "../abstractcolumn.h"

namespace Model {

class SampleSpacingMeterColumn: public AbstractColumn
{
public:
    using AbstractColumn::AbstractColumn;

    virtual QVariant data(const Core::Reflectogram &r) const;
    virtual SetResults setData(Core::Reflectogram &, const QVariant &) const;
};

} // namespace Model

#endif // SAMPLESPACINGMETERCOLUMN_H
