#ifndef GENERALPARAMETERSBLOCK_H
#define GENERALPARAMETERSBLOCK_H

#include "../fields/intfield.h"
#include "../fields/fixedstringfield.h"
#include "../fields/stringfield.h"

#include "../mappingblock.h"

namespace Core {

enum class GeneralParameters {
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

template<>
struct IdMap<GeneralParameters>: IdMapBase<
    IdMapItem<GeneralParameters, GeneralParameters::Language, String2Field>,
    IdMapItem<GeneralParameters, GeneralParameters::CableId, StringField>,
    IdMapItem<GeneralParameters, GeneralParameters::FiberId, StringField>,
    IdMapItem<GeneralParameters, GeneralParameters::Wavelength, LittleUInt16Field>,
    IdMapItem<GeneralParameters, GeneralParameters::LocationA, StringField>,
    IdMapItem<GeneralParameters, GeneralParameters::LocationB, StringField>,
    IdMapItem<GeneralParameters, GeneralParameters::CableCode, StringField>,
    IdMapItem<GeneralParameters, GeneralParameters::BuildCondition, String2Field>,
    IdMapItem<GeneralParameters, GeneralParameters::Operator, StringField>,
    IdMapItem<GeneralParameters, GeneralParameters::Comments, StringField>
>{};

class GeneralParametersBlock: public MappingBlock<GeneralParameters>
{
public:
    virtual bool readChildren(AbstractInputBuffer &buffer);
};

} // namespace Core

#endif // GENERALPARAMETERSBLOCK_H
