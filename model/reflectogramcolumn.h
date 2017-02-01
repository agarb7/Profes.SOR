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
    DateTime,
    Wavelength, // in nanometers
    PulseWidth, // in nanoseconds
    SampleSpacing, // in picoseconds
    IndexOfRefraction,
    BackscatteringCoefficient,
    FiberStartPosition, // in nanoseconds
    Points,
    SampleSpacingMeter
};

static constexpr std::size_t ReflectogramColumnCount
    = std::size_t(ReflectogramColumn::SampleSpacingMeter) + 1;

} // namespace Model

#endif // REFLECTOGRAMCOLUMN_H
