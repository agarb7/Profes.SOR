#include "supplierparametersblock.h"

#include "../fields/stringfield.h"

#include "../abstractinputbuffer.h"

bool SupplierParametersBlock::readChildren(AbstractInputBuffer &buffer)
{
    return createChild<StringField>(SupplierName)->read(buffer)
            && createChild<StringField>(OtdrName)->read(buffer)
            && createChild<StringField>(OtdrSerialNumber)->read(buffer)
            && createChild<StringField>(ModuleName)->read(buffer)
            && createChild<StringField>(ModuleSerialNumber)->read(buffer)
            && createChild<StringField>(SoftwareVersion)->read(buffer)
            && createChild<StringField>(Other)->read(buffer);
}
