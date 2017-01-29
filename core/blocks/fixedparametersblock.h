#ifndef FIXEDPARAMETERSBLOCK_H
#define FIXEDPARAMETERSBLOCK_H

#include "../fields/intfield.h"
#include "../fields/fixedstringfield.h"

#include "../mappingblock.h"

namespace Core {

enum class FixedParameters {
    DateTime,
    Units,
    Wavelength,
    PulseWidth,
    SampleSpacing,
    DataPointsCount,
    IndexOfRefraction,
    BackscatteringCoefficient,
    NumberOfAverages,
    Range,
    LossThreshold,
    ReflectionThreshold,
    EndOfTransmissionThreshold
};

template<>
struct IdMap<FixedParameters>: IdMapBase<
    IdMapItem<FixedParameters, FixedParameters::DateTime, LittleUInt32Field>,
    IdMapItem<FixedParameters, FixedParameters::Units, String2Field>,
    IdMapItem<FixedParameters, FixedParameters::Wavelength, LittleUInt16Field>,
    IdMapItem<FixedParameters, FixedParameters::PulseWidth, LittleUInt16Field>,
    IdMapItem<FixedParameters, FixedParameters::SampleSpacing, LittleUInt32Field>,
    IdMapItem<FixedParameters, FixedParameters::DataPointsCount, LittleUInt32Field>,
    IdMapItem<FixedParameters, FixedParameters::IndexOfRefraction, LittleUInt32Field>,
    IdMapItem<FixedParameters, FixedParameters::BackscatteringCoefficient, LittleUInt16Field>,
    IdMapItem<FixedParameters, FixedParameters::NumberOfAverages, LittleUInt32Field>,
    IdMapItem<FixedParameters, FixedParameters::Range, LittleUInt32Field>,
    IdMapItem<FixedParameters, FixedParameters::LossThreshold, LittleUInt16Field>,
    IdMapItem<FixedParameters, FixedParameters::ReflectionThreshold, LittleUInt16Field>,
    IdMapItem<FixedParameters, FixedParameters::EndOfTransmissionThreshold, LittleUInt16Field>
>{};

class FixedParametersBlock: public MappingBlock<FixedParameters>
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);
};

} // namespace Core

#endif // FIXEDPARAMETERSBLOCK_H
