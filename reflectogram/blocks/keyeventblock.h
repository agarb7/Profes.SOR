#ifndef KEYEVENTBLOCK_H
#define KEYEVENTBLOCK_H

#include "../block.h"

class KeyEventBlock: public Block
{
public:
    enum {
        EventNo,
        UnadjustedDistance,
        Slope,
        SpliceLoss,
        ReflectionLoss,
        EventType,
        Comments
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);
};

#endif // KEYEVENTBLOCK_H
