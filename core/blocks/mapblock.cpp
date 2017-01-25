#include "mapblock.h"

#include "mapitemblock.h"

#include "../fields/intfield.h"
#include "../fields/stringfield.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool MapBlock::readChildren(AbstractInputBuffer &buffer)
{
    if (!createChild<LittleUInt16Field>(Version)->read(buffer))
        return false;

    auto size = createChild<LittleUInt32Field>(Size);
    if (!size->read(buffer))
        return false;

    sizeChanged.connect([size](SizeType, SizeType newSize){
        size->setValue(newSize);
    });

    auto count = createChild<LittleUInt16Field>(ItemsCount);
    if (!count->read(buffer))
        return false;

    for (SizeType i=1, n=count->value(); i<n; ++i) {
        if (!createChild<MapItemBlock>()->readChildren(buffer))
            return false;
    }

    return true;
}

MapBlock::ItemIterator MapBlock::itemsBegin() const
{
    return ItemIterator(childrenBegin()+ItemsOffset);
}

MapBlock::ItemIterator MapBlock::itemsEnd() const
{
    return ItemIterator(childrenEnd());
}

} // namespace Core
