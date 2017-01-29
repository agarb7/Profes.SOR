#include "mapitemblock.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool MapItemBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<MapItem::Name>()->read(buffer)
            && createChild<MapItem::Version>()->read(buffer)
            && createChild<MapItem::Size>()->read(buffer);
}

Main MapItemBlock::mainChildId() const
{
    auto name = child<MapItem::Name>();
    if (!name)
        return Main::InvalidId;

    auto it = m_mainChildIdMap.find(name->value());
    return it != m_mainChildIdMap.end()
            ? it->second
            : Main::InvalidId;
}

const MapItemBlock::IdMap MapItemBlock::m_mainChildIdMap = {
    {"GenParams",     Main::GeneralParameters},
    {"SupParams",     Main::SupplierParameters},
    {"FxdParams",     Main::FixedParameters},
    {"KeyEvents",     Main::KeyEvents},
    {"LnkParams",     Main::LinkParameters},
    {"DataPts",       Main::DataPoints},
    {"NetTekOTDR1.0", Main::NetTekOtdr10},
    {"Cksum",         Main::Checksum}
};

} // namespace Core
