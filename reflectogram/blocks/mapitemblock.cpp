#include "mapitemblock.h"

#include "mainblockchildid.h"

#include "../fields/intfield.h"
#include "../fields/stringfield.h"

#include "../abstractinputbuffer.h"

using Rci = MainBlockChildId;

bool MapItemBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<StringField>(Name)->read(buffer)
            && createChild<LittleUInt16Field>(Version)->read(buffer)
            && createChild<LittleUInt32Field>(Size)->read(buffer);
}

int MapItemBlock::reflectogramChildId() const
{
    auto name = child<StringField>(Name);
    if (!name)
        return -1;

    auto it = m_reflectogramChildIdMap.find(name->value());
    return it != m_reflectogramChildIdMap.end()
            ? it->second
            : -1;
}

const MapItemBlock::IdMap MapItemBlock::m_reflectogramChildIdMap = {
    {"GenParams",     Rci::GeneralParameters},
    {"SupParams",     Rci::SupplierParameters},
    {"FxdParams",     Rci::FixedParameters},
    {"KeyEvents",     Rci::KeyEvents},
    {"LnkParams",     Rci::LinkParameters},
    {"DataPts",       Rci::DataPoints},
    {"NetTekOTDR1.0", Rci::NetTekOtdr10},
    {"Cksum",         Rci::Checksum}
};

