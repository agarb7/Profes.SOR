#ifndef DATAPOINTSBLOCK_H
#define DATAPOINTSBLOCK_H

#include "../block.h"

namespace Core {

class DataPointsBlock: public Block
{
public:
    enum {
        PointsCount,
        ScalingFactor,
        Points
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);
};

} // namespace Core

#endif // DATAPOINTSBLOCK_H
