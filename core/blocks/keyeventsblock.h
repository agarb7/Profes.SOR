#ifndef KEYEVENTSBLOCK_H
#define KEYEVENTSBLOCK_H

#include "../fields/intfield.h"

#include "../mappingblock.h"

namespace Core {

class KeyEventsItemBlock;

enum class KeyEvents {
    EventsCount,
    TotalLoss,
    FiberStartPosition,
    FiberLength,
    OpticalReturnLoss
};

template<>
struct IdMap<KeyEvents>: IdMapBase<
    IdMapItem<KeyEvents, KeyEvents::EventsCount, LittleUInt16Field>,
    IdMapItem<KeyEvents, KeyEvents::TotalLoss, LittleInt32Field>,
    IdMapItem<KeyEvents, KeyEvents::FiberStartPosition, LittleInt32Field>,
    IdMapItem<KeyEvents, KeyEvents::FiberLength, LittleUInt32Field>,
    IdMapItem<KeyEvents, KeyEvents::OpticalReturnLoss, LittleUInt16Field>
>{};

class KeyEventsBlock: public MappingBlock<KeyEvents>
{
public:
    using EventIterator = CastingChildIterator<KeyEventsItemBlock>;

    virtual bool readChildren(AbstractInputBuffer &buffer);

    EventIterator eventsBegin() const;
    EventIterator eventsEnd() const;

private:
    static constexpr int m_eventsOffset = 1;
};

} // namespace Core

#endif // KEYEVENTSBLOCK_H
