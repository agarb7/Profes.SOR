#ifndef SAMPLESPACINGMETERCOLUMN_H
#define SAMPLESPACINGMETERCOLUMN_H

#include "../abstractcolumn.h"

namespace Model {

class SampleSpacingMeterColumn: public AbstractColumn
{
public:
    using AbstractColumn::AbstractColumn;

    QVariant data(const Core::Reflectogram &r) const override;
    SetResults setData(Core::Reflectogram &, const QVariant &) const override;
};

} // namespace Model

#endif // SAMPLESPACINGMETERCOLUMN_H
