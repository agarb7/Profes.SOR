#ifndef REFLECTOGRAMCOLUMN_H
#define REFLECTOGRAMCOLUMN_H

#include <cstddef>

namespace Model {

enum class ReflectogramColumn {
    FilePath,
    SupplierName,
    OtdrName,
    OtdrSerialNumber,
    ModuleName,
    ModuleSerialNumber,
    SoftwareVersion,
    SupplierOther,
    Date,
    Time,
    Wavelength, // in nanometers
    PulseWidth, // in nanoseconds
    SampleSpacing, // in picoseconds
    SampleSpacingMeter, // in meters
    IndexOfRefraction,
    BackscatteringCoefficient,
    Range, // in kilometers
    FiberStartPosition, // in nanoseconds
    FiberLength, // in nanoseconds
    Points
};

static constexpr std::size_t ReflectogramColumnCount
    = std::size_t(ReflectogramColumn::Points) + 1;

} // namespace Model

#endif // REFLECTOGRAMCOLUMN_H
