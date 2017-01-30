#include "columnmap.h"

#include "core/reflectogram.h"

#include "columns/intcolumn.h"
#include "columns/stringcolumn.h"
#include "columns/doublecolumn.h"
#include "columns/datetimecolumn.h"
#include "columns/pointscolumn.h"
#include "columns/samplespacingmetercolumn.h"

#ifndef NDEBUG
#   include <algorithm>
#   include <iterator>
#endif

ColumnMap::ColumnMap()
{
    setup(
        ReflectogramModelColumn::SupplierName,
        new StringColumn<Core::Reflectogram::SupplierName>(
            tr("Supplier name")
        )
    );

    setup(
        ReflectogramModelColumn::OtdrName,
        new StringColumn<Core::Reflectogram::OtdrName>(
            tr("Otdr name")
        )
    );

    setup(
        ReflectogramModelColumn::OtdrSerialNumber,
        new StringColumn<Core::Reflectogram::OtdrSerialNumber>(
            tr("Otdr s/n")
        )
    );

    setup(
        ReflectogramModelColumn::ModuleName,
        new StringColumn<Core::Reflectogram::ModuleName>(
            tr("Module name")
        )
    );

    setup(
        ReflectogramModelColumn::ModuleSerialNumber,
        new StringColumn<Core::Reflectogram::ModuleSerialNumber>(
            tr("Module s/n")
        )
    );

    setup(
        ReflectogramModelColumn::SoftwareVersion,
        new StringColumn<Core::Reflectogram::SoftwareVersion>(
            tr("Software version")
        )
    );

    setup(
        ReflectogramModelColumn::SupplierOther,
        new StringColumn<Core::Reflectogram::SupplierOther>(
            tr("Supplier other")
        )
    );

    setup(
        ReflectogramModelColumn::DateTime,
        new DateTimeColumn(
            tr("Date/time")
        )
    );

    setup(
        ReflectogramModelColumn::Wavelength,
        new DoubleColumn<Core::Reflectogram::Wavelength>(
            tr("Wavelength"),
            10
        )
    );

    setup(
        ReflectogramModelColumn::PulseWidth,
        new IntColumn<Core::Reflectogram::PulseWidth>(
            tr("Pulse width")
        )
    );

    setup(
        ReflectogramModelColumn::SampleSpacing,
        new DoubleColumn<Core::Reflectogram::SampleSpacing>(
            tr("Sample spacing"),
            100
        )
    );

    setup(
        ReflectogramModelColumn::IndexOfRefraction,
        new DoubleColumn<Core::Reflectogram::IndexOfRefraction>(
            tr("Index of refraction"),
            100000
        )
    );

    setup(
        ReflectogramModelColumn::BackscatteringCoefficient,
        new DoubleColumn<Core::Reflectogram::BackscatteringCoefficient>(
            tr("Backscattering coef."),
            -10
        )
    );

    setup(
        ReflectogramModelColumn::FiberStartPosition,
        new DoubleColumn<Core::Reflectogram::FiberStartPosition>(
            tr("Fiber start position"),
            10
        )
    );

    setup(
        ReflectogramModelColumn::Points,
        new PointsColumn(
            tr("Trace")
        )
    );

    setup(
        ReflectogramModelColumn::SampleSpacingMeter,
        new SampleSpacingMeterColumn(
            tr("Sample spacing (m)")
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

AbstractColumn *ColumnMap::column(ReflectogramModelColumn id) const
{
    return m_map[std::size_t(id)].get();
}

void ColumnMap::setup(ReflectogramModelColumn id, AbstractColumn *column)
{
    m_map[std::size_t(id)].reset(column);
}

