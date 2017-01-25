#ifndef FIXEDPARAMETERSBLOCK_H
#define FIXEDPARAMETERSBLOCK_H

#include "../block.h"

namespace Core {

class FixedParametersBlock: public Block
{
public:
    enum {
        DateTime,
        Units,
        Wavelength,
        PulseWidth,
        SampleSpacing,
        DataPointsCount,
        IndexOfRefraction,
        BackscatteringCoefficient,
        NumberOfAverages,
        Range,
        LossThreshold,
        ReflectionThreshold,
        EndOfTransmissionThreshold
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);
};

} // namespace Core

#endif // FIXEDPARAMETERSBLOCK_H
