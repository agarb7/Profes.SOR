#include "keyeventsblock.h"

#include "keyeventblock.h"

#include "../fields/intfield.h"

#include "../abstractinputbuffer.h"

bool KeyEventsBlock::readChildren(AbstractInputBuffer &buffer)
{
    auto count = createChild<LittleUInt16Field>(EventsCount);
    if (!count->read(buffer))
        return false;

    for (SizeType i=0, n=count->value(); i<n; ++i) {
        if (!createChild<KeyEventBlock>()->readChildren(buffer))
            return false;
    }

    LittleInt32Field *fiberStart;
    LittleUInt32Field *fiberLength;
    LittleInt32Field *fiberStartCopy;
    LittleUInt32Field *fiberLengthCopy;

    bool result = createChild<LittleInt32Field>(TotalLoss)->read(buffer)
            && (fiberStart = createChild<LittleInt32Field>(FiberStartPosition))
                ->read(buffer)
            && (fiberLength = createChild<LittleUInt32Field>(FiberLength))
                ->read(buffer)
            && createChild<LittleUInt16Field>(OpticalReturnLoss)->read(buffer)
            && (fiberStartCopy = createChild<LittleInt32Field>())
                ->read(buffer)
            && (fiberLengthCopy = createChild<LittleUInt32Field>())
                ->read(buffer);

    if (!result)
        return false;

    fiberStart->valueChanged.connect([fiberStartCopy](LittleInt32 value) {
        fiberStartCopy->setValue(value);
    });

    fiberLength->valueChanged.connect([fiberLengthCopy](LittleUInt32 value) {
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
