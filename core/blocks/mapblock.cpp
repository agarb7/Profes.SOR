#include "mapblock.h"

#include "mapitemblock.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool MapBlock::readChildren(AbstractInputBuffer &buffer)
{
    if (!createChild<Map::Version>()->read(buffer))
        return false;

    auto size = createChild<Map::Size>();
    if (!size->read(buffer))
        return false;

    sizeChanged.connect([size](SizeType, SizeType newSize){
        size->setValue(newSize);
    });

    auto count = createChild<Map::ItemsCount>();
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
    return ItemIterator(childrenBegin()+m_itemsOffset);
}

MapBlock::ItemIterator MapBlock::itemsEnd() const
{
    return ItemIterator(childrenEnd());
}

} // namespace Core
