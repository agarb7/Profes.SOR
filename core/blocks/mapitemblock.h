#ifndef MAPITEMBLOCK_H
#define MAPITEMBLOCK_H

#include "mainchildid.h"

#include "../fields/intfield.h"
#include "../fields/stringfield.h"

#include "../mappingblock.h"

#include <unordered_map>

namespace Core {

enum class MapItem {
    Name,
    Version,
    Size
};

template<>
struct IdMap<MapItem>: IdMapBase<
    IdMapItem<MapItem, MapItem::Name, StringField>,
    IdMapItem<MapItem, MapItem::Version, LittleUInt16Field>,
    IdMapItem<MapItem, MapItem::Size, LittleUInt32Field>
>{};

class MapItemBlock: public MappingBlock<MapItem>
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);

    Main mainChildId() const;

private:
    using IdMap = std::unordered_map<String, Main>;

    static const IdMap m_mainChildIdMap;
};

} // namespace Core

#endif // MAPITEMBLOCK_H
