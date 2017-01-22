#ifndef RAWBLOCK_H
#define RAWBLOCK_H

#include "../block.h"

class RawBlock: public Block
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);

    SizeType readingSize() const;
    void setReadingSize(const SizeType &readingSize);

private:
    SizeType m_readingSize = 0;
};

#endif // RAWBLOCK_H
