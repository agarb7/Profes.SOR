#include "checksumblock.h"

#include <boost/crc.hpp>

#include <algorithm>

namespace Core {

bool ChecksumBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<Checksum::Checksum>()->read(buffer);
}

void ChecksumBlock::calculate(Node::DataIterator first, Node::DataIterator last)
{
    auto chksum = child<Checksum::Checksum>();
    if (!chksum)
        return;

    boost::crc_optimal<16, 0x1021, 0xFFFF, 0, false, false> crcCcitt;

    crcCcitt = std::for_each(first, last, crcCcitt);

    chksum->setValue(crcCcitt());
}

} // namespace Core
