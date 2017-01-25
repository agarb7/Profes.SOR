#include "fixedparametersblock.h"

#include "../fields/intfield.h"
#include "../fields/fixedstringfield.h"
#include "../fields/fixedrawfield.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool FixedParametersBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<LittleUInt32Field>(DateTime)->read(buffer)
            && createChild<String2Field>(Units)->read(buffer)
            && createChild<LittleUInt16Field>(Wavelength)->read(buffer)
            && createChild<FixedRawField<6>>()->read(buffer)
            && createChild<LittleUInt16Field>(PulseWidth)->read(buffer)
            && createChild<LittleUInt32Field>(SampleSpacing)->read(buffer)
            && createChild<LittleUInt32Field>(DataPointsCount)->read(buffer)
            && createChild<LittleUInt32Field>(IndexOfRefraction)->read(buffer)
            && createChild<LittleUInt16Field>(BackscatteringCoefficient)->read(buffer)
            && createChild<LittleUInt32Field>(NumberOfAverages)->read(buffer)
            && createChild<LittleUInt32Field>(Range)->read(buffer)
            && createChild<FixedRawField<10>>()->read(buffer)
            && createChild<LittleUInt16Field>(LossThreshold)->read(buffer)
            && createChild<LittleUInt16Field>(ReflectionThreshold)->read(buffer)
            && createChild<LittleUInt16Field>(EndOfTransmissionThreshold)->read(buffer);
}

} // namespace Core
