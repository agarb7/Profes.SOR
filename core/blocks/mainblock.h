#ifndef MAINBLOCK_H
#define MAINBLOCK_H

#include "mainchildid.h"

#include "../mappingblock.h"

namespace Core {

class RawBlock;

class MainBlock : public MappingBlock<Main>
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);

private:    
    Block *createChildById(Main id, SizeType size);

    RawBlock *createRawChild(SizeType size);

    template <Main Id>
    Block *createRawChild(SizeType size)
    {
        auto raw = createChild<Id>();
        raw->setReadingSize(size);

        return raw;
    }

    void connectWavelengths();
    void connectDataPointsCount();
};

} // namespace Core

#endif // MAINBLOCK_H
