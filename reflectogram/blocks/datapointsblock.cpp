#include "datapointsblock.h"

#include "../fields/intfield.h"
#include "../fields/fixedrawfield.h"
#include "../fields/littleuint16vectorfield.h"

#include "../abstractinputbuffer.h"

bool DataPointsBlock::readChildren(AbstractInputBuffer &buffer)
{
    LittleUInt32Field *count;
    LittleUInt32Field *countCopy;

    bool readed =
            (count = createChild<LittleUInt32Field>(PointsCount))
                ->read(buffer)
            && createChild<FixedRawField<2>>()->read(buffer)
            && (countCopy = createChild<LittleUInt32Field>())
                ->read(buffer);

    if (!readed)
        return false;

    count->valueChanged.connect([countCopy](LittleUInt32 value) {
        countCopy->setValue(value);
    });

    if (!createChild<LittleUInt16Field>(ScalingFactor)->read(buffer))
        return false;

    auto points = createChild<LittleUInt16VectorField>(Points);
    if (!points->read(buffer, count->value()))
        return false;

    points->countChanged.connect([count](SizeType value) {
        count->setValue(value);
    });

    return true;
}
