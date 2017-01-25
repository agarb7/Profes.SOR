#ifndef KEYEVENTBLOCK_H
#define KEYEVENTBLOCK_H

#include "../block.h"

namespace Core {

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

} // namespace Core

#endif // KEYEVENTBLOCK_H
