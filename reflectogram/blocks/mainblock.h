#ifndef MAINBLOCK_H
#define MAINBLOCK_H

#include "mainblockchildid.h"

#include "../block.h"

class MainBlock : public Block, public MainBlockChildId
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);

private:    
    Block *createChildById(int id, SizeType size);

    template <class RawChild>
    RawChild *createRawChild(int id, SizeType size)
    {
        auto raw = createChild<RawChild>(id);
        raw->setReadingSize(size);

        return raw;
    }

    void connectWavelengths();
    void connectDataPointsCount();
};

#endif // MAINBLOCK_H
