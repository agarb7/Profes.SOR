#include "mainblock.h"

#include "mapblock.h"
#include "mapitemblock.h"
#include "generalparametersblock.h"
#include "supplierparametersblock.h"
#include "fixedparametersblock.h"
#include "keyeventsblock.h"
#include "linkparametersblock.h"
#include "datapointsblock.h"
#include "nettekotdr10block.h"
#include "checksumblock.h"
#include "rawblock.h"

#include "../fields/intfield.h"

#include "../abstractinputbuffer.h"

#include <functional>

bool MainBlock::readChildren(AbstractInputBuffer &buffer)
{
    auto map = createChild<MapBlock>(Map);
    if (!map->readChildren(buffer))
        return false;    

    for (auto itemIt = map->itemsBegin(), end = map->itemsEnd();
         itemIt != end; ++itemIt)
    {
        const MapItemBlock *item = *itemIt;
        LittleUInt32Field *itemSize = item->child<LittleUInt32Field>(MapItemBlock::Size);

        Block *child = createChildById(item->reflectogramChildId(),
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

Block *MainBlock::createChildById(int id, SizeType size)
{
    switch (id) {
    case GeneralParameters:
        return createChild<GeneralParametersBlock>(GeneralParameters);
    case SupplierParameters:
        return createChild<SupplierParametersBlock>(SupplierParameters);
    case FixedParameters:
        return createChild<FixedParametersBlock>(FixedParameters);
    case KeyEvents:
        return createChild<KeyEventsBlock>(KeyEvents);
    case LinkParameters:
        return createRawChild<LinkParametersBlock>(LinkParameters, size);
    case DataPoints:
        return createChild<DataPointsBlock>(DataPoints);
    case NetTekOtdr10:
        return createRawChild<NetTekOtdr10Block>(NetTekOtdr10, size);
    case Checksum:
        return createChild<ChecksumBlock>(Checksum);
    default:
        return createRawChild<RawBlock>(-1, size);
    }
}

void MainBlock::connectWavelengths()
{
    auto genWavelength = descendant<LittleUInt16Field>(GeneralParameters,
                                                       GeneralParametersBlock::Wavelength);

    if (!genWavelength)
        return;

    auto fxdWavelength = descendant<LittleUInt16Field>(FixedParameters,
                                                       FixedParametersBlock::Wavelength);

    if (!fxdWavelength)
        return;

    fxdWavelength->valueChanged.connect([genWavelength](LittleUInt16 value) {
        genWavelength->setValue(value/10);
    });
}

void MainBlock::connectDataPointsCount()
{
    auto fxdPointsCount = descendant<LittleUInt32Field>(FixedParameters,
                                                        FixedParametersBlock::DataPointsCount);

    if (!fxdPointsCount)
        return;

    auto dataPtsCount = descendant<LittleUInt32Field>(DataPoints,
                                                      DataPointsBlock::PointsCount);

    if (!dataPtsCount)
        return;

    dataPtsCount->valueChanged.connect([fxdPointsCount](LittleUInt32 count) {
        fxdPointsCount->setValue(count);
    });
}
