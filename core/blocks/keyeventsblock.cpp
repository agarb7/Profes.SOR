#include "keyeventsblock.h"

#include "keyeventsitemblock.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool KeyEventsBlock::readChildren(AbstractInputBuffer &buffer)
{
    auto count = createChild<KeyEvents::EventsCount>();
    if (!count->read(buffer))
        return false;

    for (SizeType i=0, n=count->value(); i<n; ++i) {
        if (!createChild<KeyEventsItemBlock>()->readChildren(buffer))
            return false;
    }

    LittleInt32Field *fiberStart;
    LittleUInt32Field *fiberLength;
    LittleInt32Field *fiberStartCopy;
    LittleUInt32Field *fiberLengthCopy;

    bool result = createChild<KeyEvents::TotalLoss>()->read(buffer)
            && (fiberStart = createChild<KeyEvents::FiberStartPosition>())
                ->read(buffer)
            && (fiberLength = createChild<KeyEvents::FiberLength>())
                ->read(buffer)
            && createChild<KeyEvents::OpticalReturnLoss>()->read(buffer)
            && (fiberStartCopy = createChild<LittleInt32Field>())
                ->read(buffer)
            && (fiberLengthCopy = createChild<LittleUInt32Field>())
                ->read(buffer);

    if (!result)
        return false;

    fiberStart->valueChanged.connect([fiberStartCopy](LeInt32 value) {
        fiberStartCopy->setValue(value);
    });

    fiberLength->valueChanged.connect([fiberLengthCopy](LeUInt32 value) {
        fiberLengthCopy->setValue(value);
    });

    return result;
}

KeyEventsBlock::EventIterator KeyEventsBlock::eventsBegin() const
{
    return EventIterator(childrenBegin() + m_eventsOffset);
}

KeyEventsBlock::EventIterator KeyEventsBlock::eventsEnd() const
{
    return EventIterator(childrenEnd());
}

} // namespace Core
