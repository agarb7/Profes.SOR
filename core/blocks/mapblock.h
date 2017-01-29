#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "../fields/intfield.h"
#include "../fields/stringfield.h"

#include "../mappingblock.h"

namespace Core {

class MapItemBlock;

enum class Map {
    Version,
    Size,
    ItemsCount
};

template<>
struct IdMap<Map>: IdMapBase<
    IdMapItem<Map, Map::Version, LittleUInt16Field>,
    IdMapItem<Map, Map::Size, LittleUInt32Field>,
    IdMapItem<Map, Map::ItemsCount, LittleUInt16Field>
>{};

class MapBlock: public MappingBlock<Map>
{
public:
    using ItemIterator = CastingChildIterator<MapItemBlock>;

    virtual bool readChildren(AbstractInputBuffer &buffer);

    ItemIterator itemsBegin() const;
    ItemIterator itemsEnd() const;

private:
    static constexpr int m_itemsOffset = IdMap<Map>::size;
};

} // namespace Core

#endif // MAPBLOCK_H
