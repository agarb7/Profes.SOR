#include "fixedparametersblock.h"

#include "../fields/fixedrawfield.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool FixedParametersBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<FixedParameters::DateTime>()->read(buffer)
            && createChild<FixedParameters::Units>()->read(buffer)
            && createChild<FixedParameters::Wavelength>()->read(buffer)
            && createChild<FixedRawField<6>>()->read(buffer)
            && createChild<FixedParameters::PulseWidth>()->read(buffer)
            && createChild<FixedParameters::SampleSpacing>()->read(buffer)
            && createChild<FixedParameters::DataPointsCount>()->read(buffer)
            && createChild<FixedParameters::IndexOfRefraction>()->read(buffer)
            && createChild<FixedParameters::BackscatteringCoefficient>()->read(buffer)
            && createChild<FixedParameters::NumberOfAverages>()->read(buffer)
            && createChild<FixedParameters::Range>()->read(buffer)
            && createChild<FixedRawField<10>>()->read(buffer)
            && createChild<FixedParameters::LossThreshold>()->read(buffer)
            && createChild<FixedParameters::ReflectionThreshold>()->read(buffer)
            && createChild<FixedParameters::EndOfTransmissionThreshold>()->read(buffer);
}

} // namespace Core
