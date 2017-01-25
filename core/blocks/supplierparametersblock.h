#ifndef SUPPLIERPARAMETERSBLOCK_H
#define SUPPLIERPARAMETERSBLOCK_H

#include "../block.h"

namespace Core {

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

} // namespace Core

#endif // SUPPLIERPARAMETERSBLOCK_H
