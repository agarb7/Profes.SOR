#include "keyeventblock.h"

#include "../fields/intfield.h"
#include "../fields/fixedstringfield.h"
#include "../fields/stringfield.h"

#include "../abstractinputbuffer.h"

bool KeyEventBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<LittleUInt16Field>(EventNo)->read(buffer)
            && createChild<LittleUInt32Field>(UnadjustedDistance)->read(buffer)
            && createChild<LittleInt16Field>(Slope)->read(buffer)
            && createChild<LittleInt16Field>(SpliceLoss)->read(buffer)
            && createChild<LittleInt32Field>(ReflectionLoss)->read(buffer)
            && createChild<FixedStringField<8>>(EventType)->read(buffer)
            && createChild<StringField>(Comments)->read(buffer);
}

