#include "generalparametersblock.h"

#include "../fields/intfield.h"
#include "../fields/fixedstringfield.h"
#include "../fields/stringfield.h"
#include "../fields/fixedrawfield.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool GeneralParametersBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<String2Field>(Language)->read(buffer)
            && createChild<StringField>(CableId)->read(buffer)
            && createChild<StringField>(FiberId)->read(buffer)
            && createChild<LittleUInt16Field>(Wavelength)->read(buffer)
            && createChild<StringField>(LocationA)->read(buffer)
            && createChild<StringField>(LocationB)->read(buffer)
            && createChild<StringField>(CableCode)->read(buffer)
            && createChild<String2Field>(BuildCondition)->read(buffer)
            && createChild<FixedRawField<4>>()->read(buffer) // it is diff from desc (Blog), and may be is offset
            && createChild<StringField>(Operator)->read(buffer)
            && createChild<StringField>(Comments)->read(buffer);
}

} // namespace Core
