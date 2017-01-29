#ifndef KEYEVENTSITEMBLOCK_H
#define KEYEVENTSITEMBLOCK_H

#include "../fields/intfield.h"
#include "../fields/fixedstringfield.h"
#include "../fields/stringfield.h"

#include "../mappingblock.h"

namespace Core {

enum class KeyEventsItem {
    EventNo,
    UnadjustedDistance,
    Slope,
    SpliceLoss,
    ReflectionLoss,
    EventType,
    Comments
};

template<>
struct IdMap<KeyEventsItem>: IdMapBase<
    IdMapItem<KeyEventsItem, KeyEventsItem::EventNo, LittleUInt16Field>,
    IdMapItem<KeyEventsItem, KeyEventsItem::UnadjustedDistance, LittleUInt32Field>,
    IdMapItem<KeyEventsItem, KeyEventsItem::Slope, LittleInt16Field>,
    IdMapItem<KeyEventsItem, KeyEventsItem::SpliceLoss, LittleInt16Field>,
    IdMapItem<KeyEventsItem, KeyEventsItem::ReflectionLoss, LittleInt32Field>,
    IdMapItem<KeyEventsItem, KeyEventsItem::EventType, FixedStringField<8>>,
    IdMapItem<KeyEventsItem, KeyEventsItem::Comments, StringField>
>{};

class KeyEventsItemBlock: public MappingBlock<KeyEventsItem>
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);
};

} // namespace Core

#endif // KEYEVENTSITEMBLOCK_H
