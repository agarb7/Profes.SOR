#ifndef REFLECTOGRAM_H
#define REFLECTOGRAM_H

#include "blocks/mainblock.h"

#include "definitions.h"

#include <memory>

class AbstractInputBuffer;

class Reflectogram
{    
public:
    using DataIterator = Block::DataIterator;

    bool read(AbstractInputBuffer& buffer);

    DataIterator dataBegin() const;
    DataIterator dataEnd() const;

    void calculateChecksum();

    String supplierName() const;
    void setSupplierName(const String &name);

    String otdrName() const;
    void setOtdrName(const String &name);

    String otdrSerialNumber() const;
    void setOtdrSerialNumber(const String &sn);

    String moduleName() const;
    void setModuleName(const String &name);

    String moduleSerialNumber() const;
    void setModuleSerialNumber(const String &sn);

    String softwareVersion() const;
    void setSoftwareVersion(const String &version);

    String other() const;
    void setOther(const String &other);

    LittleUInt32 dateTime() const;
    void setDateTime(LittleUInt32 dateTime);

    LittleUInt16 wavelength() const;
    void setWavelength(LittleUInt16 wavelength);

    LittleUInt16 pulseWidth() const;
    void setPulseWidth(LittleUInt16 pulseWidth);

    LittleUInt32 sampleSpacing() const;
    void setSampleSpacing(LittleUInt32 spacing);

    LittleUInt32 indexOfRefraction() const;
    void setIndexOfRefraction(LittleUInt32 ior);

    LittleUInt16 backscatteringCoefficient() const;
    void setBackscatteringCoefficient(LittleUInt16 coef);

    LittleInt32 fiberStartPosition() const;
    void setFiberStartPosition(LittleInt32 startPos);

    LittleUInt16 scalingFactor() const;
    void setScalingFactor(LittleUInt16 factor);

    LittleUInt16Vector points() const;
    void setPoints(LittleUInt16Vector points);

private:
    template<class Field, class ...Ids>
    typename Field::ValueType value(Ids ...ids) const;

    template<class Field, class ...Ids>
    void setValue(const typename Field::ValueType &value, Ids ...ids);

    std::unique_ptr<MainBlock> m_mainBlock;
};

#endif // REFLECTOGRAM_H
