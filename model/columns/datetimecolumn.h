#ifndef DATETIMECOLUMN_H
#define DATETIMECOLUMN_H

#include "typedcolumn.h"

#include "core/reflectogram.h"

#include <QDateTime>

namespace Model {

class DateTimeColumn: public TypedColumn<QDateTime, Core::Reflectogram::DateTime>
{
public:
    using TypedColumn<QDateTime, Core::Reflectogram::DateTime>::TypedColumn;

protected:
    virtual CoreValueType toCoreValue(const QDateTime &modelValue,
                                      const Core::Reflectogram &) const
    {
        return modelValue.toTime_t();
    }

    virtual QDateTime toModelValue(const CoreValueType &coreValue,
                                   const Core::Reflectogram &) const
    {
        return QDateTime::fromTime_t(coreValue);
    }
};

} // namespace Model

#endif // DATETIMECOLUMN_H
