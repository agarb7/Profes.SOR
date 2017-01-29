#include "keyeventsitemblock.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool KeyEventsItemBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<KeyEventsItem::EventNo>()->read(buffer)
            && createChild<KeyEventsItem::UnadjustedDistance>()->read(buffer)
            && createChild<KeyEventsItem::Slope>()->read(buffer)
            && createChild<KeyEventsItem::SpliceLoss>()->read(buffer)
            && createChild<KeyEventsItem::ReflectionLoss>()->read(buffer)
            && createChild<KeyEventsItem::EventType>()->read(buffer)
            && createChild<KeyEventsItem::Comments>()->read(buffer);
}

} // namespace Core
