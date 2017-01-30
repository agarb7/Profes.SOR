#ifndef DATETIMECOLUMN_H
#define DATETIMECOLUMN_H

#include "typedcolumn.h"

#include "core/reflectogram.h"

#include <QDateTime>

class DateTimeColumn: public TypedColumn<QDateTime, Core::Reflectogram::DateTime>
{
public:
    using TypedColumn<QDateTime, Core::Reflectogram::DateTime>::TypedColumn;

protected:
    virtual CoreValueType toCoreValue(const QDateTime &modelValue) const
    {
        return modelValue.toTime_t();
    }

    virtual QDateTime toModelValue(const CoreValueType &coreValue) const
    {
        return QDateTime::fromTime_t(coreValue);
    }
};

#endif // DATETIMECOLUMN_H
