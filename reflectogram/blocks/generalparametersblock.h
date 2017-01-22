#ifndef GENERALPARAMETERSBLOCK_H
#define GENERALPARAMETERSBLOCK_H

#include "../block.h"

class GeneralParametersBlock: public Block
{
public:
    enum {
        Language,
        CableId,
        FiberId,
        Wavelength,
        LocationA,
        LocationB,
        CableCode,
        BuildCondition,
        Operator,
        Comments
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);
};

#endif // GENERALPARAMETERSBLOCK_H
