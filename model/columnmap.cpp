#include "columnmap.h"

#include "core/reflectogram.h"

#include "columns/intcolumn.h"
#include "columns/stringcolumn.h"
#include "columns/doublecolumn.h"
#include "columns/timepartcolumn.h"
#include "columns/pointscolumn.h"
#include "columns/samplespacingmetercolumn.h"

#ifndef NDEBUG
#   include <algorithm>
#   include <iterator>
#endif

namespace Model {

ColumnMap::ColumnMap()
{
    setup(
        ReflectogramColumn::SupplierName,
        new StringColumn<Core::Reflectogram::SupplierName>(
            tr("Supplier name")
        )
    );

    setup(
        ReflectogramColumn::OtdrName,
        new StringColumn<Core::Reflectogram::OtdrName>(
            tr("Otdr name")
        )
    );

    setup(
        ReflectogramColumn::OtdrSerialNumber,
        new StringColumn<Core::Reflectogram::OtdrSerialNumber>(
            tr("Otdr s/n")
        )
    );

    setup(
        ReflectogramColumn::ModuleName,
        new StringColumn<Core::Reflectogram::ModuleName>(
            tr("Module name")
        )
    );

    setup(
        ReflectogramColumn::ModuleSerialNumber,
        new StringColumn<Core::Reflectogram::ModuleSerialNumber>(
            tr("Module s/n")
        )
    );

    setup(
        ReflectogramColumn::SoftwareVersion,
        new StringColumn<Core::Reflectogram::SoftwareVersion>(
            tr("Software version")
        )
    );

    setup(
        ReflectogramColumn::SupplierOther,
        new StringColumn<Core::Reflectogram::SupplierOther>(
            tr("Supplier other")
        )
    );

    setup(
        ReflectogramColumn::Date,
        new DateColumn(tr("Date"))
    );

    setup(
        ReflectogramColumn::Time,
        new TimeColumn(tr("Time"))
    );

    setup(
        ReflectogramColumn::Wavelength,
        new DoubleColumn<Core::Reflectogram::Wavelength>(
            tr("Wavelength"),
            10
        )
    );

    setup(
        ReflectogramColumn::PulseWidth,
        new IntColumn<Core::Reflectogram::PulseWidth>(
            tr("Pulse width")
        )
    );

    setup(
        ReflectogramColumn::SampleSpacing,
        new DoubleColumn<Core::Reflectogram::SampleSpacing>(
            tr("Sample spacing"),
            100
        )
    );

    setup(
        ReflectogramColumn::SampleSpacingMeter,
        new SampleSpacingMeterColumn(
            tr("Sample spacing (m)")
        )
    );

    setup(
        ReflectogramColumn::IndexOfRefraction,
        new DoubleColumn<Core::Reflectogram::IndexOfRefraction>(
            tr("Index of refraction"),
            100000
        )
    );

    setup(
        ReflectogramColumn::BackscatteringCoefficient,
        new DoubleColumn<Core::Reflectogram::BackscatteringCoefficient>(
            tr("Backscattering coef."),
            -10
        )
    );

    setup(
        ReflectogramColumn::FiberStartPosition,
        new DoubleColumn<Core::Reflectogram::FiberStartPosition>(
            tr("Events: Fiber start position"),
            10
        )
    );

    setup(
        ReflectogramColumn::FiberLength,
        new DoubleColumn<Core::Reflectogram::FiberLength>(
            tr("Events: Fiber length"),
            10
        )
    );

    setup(
        ReflectogramColumn::Points,
        new PointsColumn(
            tr("Trace")
        )
    );

    assert((
        std::all_of(std::next(m_map.begin()), m_map.end(), [](const ColumnPtr &ptr){
            return bool(ptr);
        })
    ));
}

const ColumnMap &ColumnMap::instance()
{
    static ColumnMap map;
    return map;
}

AbstractColumn *ColumnMap::column(ReflectogramColumn id) const
{
    return m_map[std::size_t(id)].get();
}

void ColumnMap::setup(ReflectogramColumn id, AbstractColumn *column)
{
    m_map[std::size_t(id)].reset(column);
}

} // namespace Model
