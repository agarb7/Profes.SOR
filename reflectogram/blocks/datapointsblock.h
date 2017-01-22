#ifndef DATAPOINTSBLOCK_H
#define DATAPOINTSBLOCK_H

#include "../block.h"

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

#endif // DATAPOINTSBLOCK_H
