#include "mainblock.h"

#include "mapitemblock.h"
#include "rawblock.h"

#include "../fields/intfield.h"

#include "../abstractinputbuffer.h"

#include <functional>

namespace Core {

bool MainBlock::readChildren(AbstractInputBuffer &buffer)
{
    auto map = createChild<Main::Map>();
    if (!map->readChildren(buffer))
        return false;    

    for (auto itemIt = map->itemsBegin(), end = map->itemsEnd();
         itemIt != end; ++itemIt)
    {
        const MapItemBlock *item = *itemIt;
        LittleUInt32Field *itemSize = item->child<MapItem::Size>();

        Block *child = createChildById(item->mainChildId(),
                                       itemSize->value());

        if (!child->readChildren(buffer))
            return false;

        child->sizeChanged.connect([itemSize](SizeType, SizeType newSize) {
            itemSize->setValue(newSize);
        });
    }

    connectWavelengths();
    connectDataPointsCount();

    return true;
}

Block *MainBlock::createChildById(Main id, SizeType size)
{
    switch (id) {
    case Main::GeneralParameters:
        return createChild<Main::GeneralParameters>();

    case Main::SupplierParameters:
        return createChild<Main::SupplierParameters>();

    case Main::FixedParameters:
        return createChild<Main::FixedParameters>();

    case Main::KeyEvents:
        return createChild<Main::KeyEvents>();

    case Main::LinkParameters:
        return createRawChild<Main::LinkParameters>(size);

    case Main::DataPoints:
        return createChild<Main::DataPoints>();

    case Main::NetTekOtdr10:
        return createRawChild<Main::NetTekOtdr10>(size);

    case Main::Checksum:
        return createChild<Main::Checksum>();

    case Main::InvalidId:
    default:
        return createRawChild(size);
    }
}

RawBlock *MainBlock::createRawChild(SizeType size)
{
    auto raw = createChild<RawBlock>();
    raw->setReadingSize(size);

    return raw;
}

void MainBlock::connectWavelengths()
{
    auto genWavelength = descendant<MplVector<
        Ic<Main, Main::GeneralParameters>,
        Ic<GeneralParameters, GeneralParameters::Wavelength>
    >>();

    if (!genWavelength)
        return;

    auto fxdWavelength = descendant<MplVector<
        Ic<Main, Main::FixedParameters>,
        Ic<FixedParameters, FixedParameters::Wavelength>
    >>();

    if (!fxdWavelength)
        return;

    fxdWavelength->valueChanged.connect([genWavelength](LeUInt16 value) {
        genWavelength->setValue(value/10);
    });
}

void MainBlock::connectDataPointsCount()
{
    auto fxdPointsCount = descendant<MplVector<
        Ic<Main, Main::FixedParameters>,
        Ic<FixedParameters, FixedParameters::DataPointsCount>
    >>();

    if (!fxdPointsCount)
        return;

    auto dataPtsCount = descendant<MplVector<
        Ic<Main, Main::DataPoints>,
        Ic<DataPoints, DataPoints::PointsCount>
    >>();

    if (!dataPtsCount)
        return;

    dataPtsCount->valueChanged.connect([fxdPointsCount](LeUInt32 count) {
        fxdPointsCount->setValue(count);
    });
}

} // namespace Core
