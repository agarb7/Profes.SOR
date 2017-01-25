#ifndef RAWBLOCK_H
#define RAWBLOCK_H

#include "../block.h"

namespace Core {

class RawBlock: public Block
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);

    SizeType readingSize() const;
    void setReadingSize(const SizeType &readingSize);

private:
    SizeType m_readingSize = 0;
};

} // namespace Core

#endif // RAWBLOCK_H
