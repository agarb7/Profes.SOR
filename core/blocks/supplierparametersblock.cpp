#include "supplierparametersblock.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool SupplierParametersBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<SupplierParameters::SupplierName>()->read(buffer)
            && createChild<SupplierParameters::OtdrName>()->read(buffer)
            && createChild<SupplierParameters::OtdrSerialNumber>()->read(buffer)
            && createChild<SupplierParameters::ModuleName>()->read(buffer)
            && createChild<SupplierParameters::ModuleSerialNumber>()->read(buffer)
            && createChild<SupplierParameters::SoftwareVersion>()->read(buffer)
            && createChild<SupplierParameters::Other>()->read(buffer);
}

} // namespace Core
