#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "../block.h"

namespace Core {

class MapItemBlock;

class MapBlock: public Block
{
public:
    using ItemIterator = CastingChildIterator<MapItemBlock>;

    enum {
        Version,
        Size,
        ItemsCount,
        ItemsOffset
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);

    ItemIterator itemsBegin() const;
    ItemIterator itemsEnd() const;
};

} // namespace Core

#endif // MAPBLOCK_H
