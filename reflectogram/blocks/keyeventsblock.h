#ifndef KEYEVENTSBLOCK_H
#define KEYEVENTSBLOCK_H

#include "../block.h"

class KeyEventBlock;

class KeyEventsBlock: public Block
{
public:
    using EventIterator = CastingChildIterator<KeyEventBlock>;

    enum {
        EventsCount,
        TotalLoss,
        FiberStartPosition,
        FiberLength,
        OpticalReturnLoss
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);

    EventIterator eventsBegin() const;
    EventIterator eventsEnd() const;

private:
    static const int m_eventsOffset = 1;
};

#endif // KEYEVENTSBLOCK_H
