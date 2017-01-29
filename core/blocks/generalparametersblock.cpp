#include "generalparametersblock.h"

#include "../fields/fixedrawfield.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool GeneralParametersBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<GeneralParameters::Language>()->read(buffer)
            && createChild<GeneralParameters::CableId>()->read(buffer)
            && createChild<GeneralParameters::FiberId>()->read(buffer)
            && createChild<GeneralParameters::Wavelength>()->read(buffer)
            && createChild<GeneralParameters::LocationA>()->read(buffer)
            && createChild<GeneralParameters::LocationB>()->read(buffer)
            && createChild<GeneralParameters::CableCode>()->read(buffer)
            && createChild<GeneralParameters::BuildCondition>()->read(buffer)
            && createChild<FixedRawField<4>>()->read(buffer) // it is diff from desc (Blog), and may be is offset
            && createChild<GeneralParameters::Operator>()->read(buffer)
            && createChild<GeneralParameters::Comments>()->read(buffer);
}

} // namespace Core
