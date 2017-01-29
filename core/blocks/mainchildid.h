#ifndef MAINCHILDID_H
#define MAINCHILDID_H

#include "mapblock.h"
#include "generalparametersblock.h"
#include "supplierparametersblock.h"
#include "fixedparametersblock.h"
#include "keyeventsblock.h"
#include "linkparametersblock.h"
#include "datapointsblock.h"
#include "nettekotdr10block.h"
#include "checksumblock.h"

#include "../mappingblock.h"

namespace Core {

enum class Main {
    Map,
    GeneralParameters,
    SupplierParameters,
    FixedParameters,
    KeyEvents,
    LinkParameters,
    DataPoints,
    NetTekOtdr10,
    Checksum,
    InvalidId
};

template<>
struct IdMap<Main>: IdMapBase<
    IdMapItem<Main, Main::Map, MapBlock>,
    IdMapItem<Main, Main::GeneralParameters, GeneralParametersBlock>,
    IdMapItem<Main, Main::SupplierParameters, SupplierParametersBlock>,
    IdMapItem<Main, Main::FixedParameters, FixedParametersBlock>,
    IdMapItem<Main, Main::KeyEvents, KeyEventsBlock>,
    IdMapItem<Main, Main::LinkParameters, LinkParametersBlock>,
    IdMapItem<Main, Main::DataPoints, DataPointsBlock>,
    IdMapItem<Main, Main::NetTekOtdr10, NetTekOtdr10Block>,
    IdMapItem<Main, Main::Checksum, ChecksumBlock>
>{};

} // namespace Core

#endif // MAINCHILDID_H
