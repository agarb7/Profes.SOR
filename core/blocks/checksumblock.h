#ifndef CHECKSUMBLOCK_H
#define CHECKSUMBLOCK_H

#include "../mappingblock.h"

#include "../fields/intfield.h"

namespace Core {

enum class Checksum {
    Checksum
};

template<>
struct IdMap<Checksum>: IdMapBase<
    IdMapItem<Checksum, Checksum::Checksum, LittleUInt16Field>
>{};

class ChecksumBlock: public MappingBlock<Checksum>
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);

    void calculate(DataIterator first, DataIterator last);
};

} // namespace Core

#endif // CHECKSUMBLOCK_H
