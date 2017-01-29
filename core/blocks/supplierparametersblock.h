#ifndef SUPPLIERPARAMETERSBLOCK_H
#define SUPPLIERPARAMETERSBLOCK_H

#include "../fields/stringfield.h"

#include "../mappingblock.h"

namespace Core {

enum class SupplierParameters {
    SupplierName,
    OtdrName,
    OtdrSerialNumber,
    ModuleName,
    ModuleSerialNumber,
    SoftwareVersion,
    Other
};

template<>
struct IdMap<SupplierParameters>: IdMapBase<
    IdMapItem<SupplierParameters, SupplierParameters::SupplierName, StringField>,
    IdMapItem<SupplierParameters, SupplierParameters::OtdrName, StringField>,
    IdMapItem<SupplierParameters, SupplierParameters::OtdrSerialNumber, StringField>,
    IdMapItem<SupplierParameters, SupplierParameters::ModuleName, StringField>,
    IdMapItem<SupplierParameters, SupplierParameters::ModuleSerialNumber, StringField>,
    IdMapItem<SupplierParameters, SupplierParameters::SoftwareVersion, StringField>,
    IdMapItem<SupplierParameters, SupplierParameters::Other, StringField>
>{};

class SupplierParametersBlock: public MappingBlock<SupplierParameters>
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);
};

} // namespace Core

#endif // SUPPLIERPARAMETERSBLOCK_H
