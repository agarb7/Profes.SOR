#ifndef FIXEDPARAMETERSBLOCK_H
#define FIXEDPARAMETERSBLOCK_H

#include "../block.h"

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

#endif // FIXEDPARAMETERSBLOCK_H
