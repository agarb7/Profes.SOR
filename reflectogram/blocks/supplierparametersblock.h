#ifndef SUPPLIERPARAMETERSBLOCK_H
#define SUPPLIERPARAMETERSBLOCK_H

#include "../block.h"

class SupplierParametersBlock: public Block
{
public:
    enum {
        SupplierName,
        OtdrName,
        OtdrSerialNumber,
        ModuleName,
        ModuleSerialNumber,
        SoftwareVersion,
        Other
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);
};

#endif // SUPPLIERPARAMETERSBLOCK_H
