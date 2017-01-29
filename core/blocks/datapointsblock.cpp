#include "datapointsblock.h"

#include "../fields/fixedrawfield.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool DataPointsBlock::readChildren(AbstractInputBuffer &buffer)
{
    LittleUInt32Field *count;
    LittleUInt32Field *countCopy;

    bool readed =
            (count = createChild<DataPoints::PointsCount>())
                ->read(buffer)
            && createChild<FixedRawField<2>>()->read(buffer)
            && (countCopy = createChild<LittleUInt32Field>())
                ->read(buffer);

    if (!readed)
        return false;

    count->valueChanged.connect([countCopy](LeUInt32 value) {
        countCopy->setValue(value);
    });

    if (!createChild<DataPoints::ScalingFactor>()->read(buffer))
        return false;

    auto points = createChild<DataPoints::Points>();
    if (!points->read(buffer, count->value()))
        return false;

    points->countChanged.connect([count](SizeType value) {
        count->setValue(value);
    });

    return true;
}

} // namespace Core
