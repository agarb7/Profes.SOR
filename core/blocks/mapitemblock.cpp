#include "mapitemblock.h"

#include "mainblockchildid.h"

#include "../fields/intfield.h"
#include "../fields/stringfield.h"

#include "../abstractinputbuffer.h"

namespace Core {

using Mbci = MainBlockChildId;

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
    {"GenParams",     Mbci::GeneralParameters},
    {"SupParams",     Mbci::SupplierParameters},
    {"FxdParams",     Mbci::FixedParameters},
    {"KeyEvents",     Mbci::KeyEvents},
    {"LnkParams",     Mbci::LinkParameters},
    {"DataPts",       Mbci::DataPoints},
    {"NetTekOTDR1.0", Mbci::NetTekOtdr10},
    {"Cksum",         Mbci::Checksum}
};

} // namespace Core
