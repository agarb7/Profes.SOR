#include "checksumblock.h"

#include "../fields/intfield.h"

#include <boost/crc.hpp>

#include <algorithm>

bool ChecksumBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<LittleUInt16Field>(Checksum)->read(buffer);
}

void ChecksumBlock::calculate(Node::DataIterator first, Node::DataIterator last)
{
    auto chksum = child<LittleUInt16Field>(Checksum);
    if (!chksum)
        return;

    boost::crc_optimal<16, 0x1021, 0xFFFF, 0, false, false> crcCcitt;

    crcCcitt = std::for_each(first, last, crcCcitt);

    chksum->setValue(crcCcitt());
}
