#ifndef DATAPOINTSBLOCK_H
#define DATAPOINTSBLOCK_H

#include "../fields/littleuint16vectorfield.h"
#include "../fields/intfield.h"

#include "../mappingblock.h"

namespace Core {

enum class DataPoints {
    PointsCount,
    ScalingFactor,
    Points
};

template<>
struct IdMap<DataPoints>: IdMapBase<
    IdMapItem<DataPoints, DataPoints::PointsCount, LittleUInt32Field>,
    IdMapItem<DataPoints, DataPoints::ScalingFactor, LittleUInt16Field>,
    IdMapItem<DataPoints, DataPoints::Points, LittleUInt16VectorField>
>{};

class DataPointsBlock: public MappingBlock<DataPoints>
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);
};

} // namespace Core

#endif // DATAPOINTSBLOCK_H
