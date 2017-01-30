#ifndef REFLECTOGRAMMODELCOLUMN_H
#define REFLECTOGRAMMODELCOLUMN_H

#include <cstddef>

enum class ReflectogramModelColumn {
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

static constexpr std::size_t ReflectogramModelColumnCount
    = std::size_t(ReflectogramModelColumn::SampleSpacingMeter) + 1;

#endif // REFLECTOGRAMMODELCOLUMN_H
