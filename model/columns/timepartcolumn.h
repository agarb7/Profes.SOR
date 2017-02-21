#ifndef TIMEPARTCOLUMN_H
#define TIMEPARTCOLUMN_H

#include "typedcolumn.h"

#include "core/reflectogram.h"

#include <QDateTime>

namespace Model {

template <class TimePart,
          TimePart (QDateTime::*timePart)() const,
          void (QDateTime::*setTimePart)(const TimePart&)>
class TimePartColumn: public TypedColumn<TimePart, Core::Reflectogram::DateTime>
{
    using Base = TypedColumn<TimePart, Core::Reflectogram::DateTime>;
    using Base::CoreField;
    using typename Base::CoreValueType;

public:    
    using Base::Base;

protected:
    CoreValueType toCoreValue(const TimePart &modelValue,
                              const Core::Reflectogram &r) const override
    {
        auto coreDateTime = r.value<CoreField>();

        auto modelDateTime = QDateTime::fromTime_t(coreDateTime);
        (modelDateTime.*setTimePart)(modelValue);

        return modelDateTime.toTime_t();
    }

    TimePart toModelValue(const CoreValueType &coreValue,
                          const Core::Reflectogram &) const override
    {
        return (QDateTime::fromTime_t(coreValue).*timePart)();
    }
};

using TimeColumn = TimePartColumn<QTime, &QDateTime::time, &QDateTime::setTime>;
using DateColumn = TimePartColumn<QDate, &QDateTime::date, &QDateTime::setDate>;

} // namespace Model

#endif // TIMEPARTCOLUMN_H
