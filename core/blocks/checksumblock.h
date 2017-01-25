#ifndef CHECKSUMBLOCK_H
#define CHECKSUMBLOCK_H

#include "../block.h"

namespace Core {

class ChecksumBlock: public Block
{
public:
    enum {
        Checksum
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);

    void calculate(DataIterator first, DataIterator last);
};

} // namespace Core

#endif // CHECKSUMBLOCK_H
