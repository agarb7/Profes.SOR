#include "reflectogram.h"

#include "blocks/supplierparametersblock.h"
#include "blocks/fixedparametersblock.h"
#include "blocks/keyeventsblock.h"
#include "blocks/datapointsblock.h"
#include "blocks/checksumblock.h"

#include "fields/stringfield.h"
#include "fields/intfield.h"
#include "fields/littleuint16vectorfield.h"

bool Reflectogram::read(AbstractInputBuffer &buffer)
{
    m_mainBlock.reset(new MainBlock);

    if (!m_mainBlock->readChildren(buffer)) {
        m_mainBlock.reset();
        return false;
    }

    return true;
}

Reflectogram::DataIterator Reflectogram::dataBegin() const
{
    return m_mainBlock
            ? m_mainBlock->dataBegin()
            : DataIterator();
}

Reflectogram::DataIterator Reflectogram::dataEnd() const
{
    return m_mainBlock
            ? m_mainBlock->dataEnd()
            : DataIterator();
}

void Reflectogram::calculateChecksum()
{
    if (!m_mainBlock)
        return;

    ChecksumBlock *chksum
            = m_mainBlock->child<ChecksumBlock>(MainBlock::Checksum);

    chksum->calculate(m_mainBlock->dataBegin(), m_mainBlock->dataIterator(chksum));
}

String Reflectogram::supplierName() const
{
    return value<StringField>(MainBlock::SupplierParameters,
                              SupplierParametersBlock::SupplierName);
}

void Reflectogram::setSupplierName(const String &name)
{
    setValue<StringField>(name,
                          MainBlock::SupplierParameters,
                          SupplierParametersBlock::SupplierName);
}

String Reflectogram::otdrName() const
{
    return value<StringField>(MainBlock::SupplierParameters,
                              SupplierParametersBlock::OtdrName);
}

void Reflectogram::setOtdrName(const String &name)
{
    setValue<StringField>(name,
                          MainBlock::SupplierParameters,
                          SupplierParametersBlock::OtdrName);
}

String Reflectogram::otdrSerialNumber() const
{
    return value<StringField>(MainBlock::SupplierParameters,
                              SupplierParametersBlock::OtdrSerialNumber);
}

void Reflectogram::setOtdrSerialNumber(const String &sn)
{
    setValue<StringField>(sn,
                          MainBlock::SupplierParameters,
                          SupplierParametersBlock::OtdrSerialNumber);
}

String Reflectogram::moduleName() const
{
    return value<StringField>(MainBlock::SupplierParameters,
                              SupplierParametersBlock::ModuleName);
}

void Reflectogram::setModuleName(const String &name)
{
    setValue<StringField>(name,
                          MainBlock::SupplierParameters,
                          SupplierParametersBlock::ModuleName);
}

String Reflectogram::moduleSerialNumber() const
{
    return value<StringField>(MainBlock::SupplierParameters,
                              SupplierParametersBlock::ModuleSerialNumber);
}

void Reflectogram::setModuleSerialNumber(const String &sn)
{
    setValue<StringField>(sn,
                          MainBlock::SupplierParameters,
                          SupplierParametersBlock::ModuleSerialNumber);
}

String Reflectogram::softwareVersion() const
{
    return value<StringField>(MainBlock::SupplierParameters,
                              SupplierParametersBlock::SoftwareVersion);
}

void Reflectogram::setSoftwareVersion(const String &version)
{
    setValue<StringField>(version,
                          MainBlock::SupplierParameters,
                          SupplierParametersBlock::SoftwareVersion);
}

String Reflectogram::other() const
{
    return value<StringField>(MainBlock::SupplierParameters,
                              SupplierParametersBlock::Other);
}

void Reflectogram::setOther(const String &other)
{
    setValue<StringField>(other,
                          MainBlock::SupplierParameters,
                          SupplierParametersBlock::Other);
}

LittleUInt32 Reflectogram::dateTime() const
{
    return value<LittleUInt32Field>(MainBlock::FixedParameters,
                                    FixedParametersBlock::DateTime);
}

void Reflectogram::setDateTime(LittleUInt32 dateTime)
{
    setValue<LittleUInt32Field>(dateTime,
                                MainBlock::FixedParameters,
                                FixedParametersBlock::DateTime);
}

LittleUInt16 Reflectogram::wavelength() const
{
    return value<LittleUInt16Field>(MainBlock::FixedParameters,
                                    FixedParametersBlock::Wavelength);
}

void Reflectogram::setWavelength(LittleUInt16 wavelength)
{
    setValue<LittleUInt16Field>(wavelength,
                                MainBlock::FixedParameters,
                                FixedParametersBlock::Wavelength);
}

LittleUInt16 Reflectogram::pulseWidth() const
{
    return value<LittleUInt16Field>(MainBlock::FixedParameters,
                                    FixedParametersBlock::PulseWidth);
}

void Reflectogram::setPulseWidth(LittleUInt16 pulseWidth)
{
    setValue<LittleUInt16Field>(pulseWidth,
                                MainBlock::FixedParameters,
                                FixedParametersBlock::PulseWidth);
}

LittleUInt32 Reflectogram::sampleSpacing() const
{
    return value<LittleUInt32Field>(MainBlock::FixedParameters,
                                    FixedParametersBlock::SampleSpacing);
}

void Reflectogram::setSampleSpacing(LittleUInt32 spacing)
{
    setValue<LittleUInt32Field>(spacing,
                                MainBlock::FixedParameters,
                                FixedParametersBlock::SampleSpacing);
}

LittleUInt32 Reflectogram::indexOfRefraction() const
{
    return value<LittleUInt32Field>(MainBlock::FixedParameters,
                                    FixedParametersBlock::IndexOfRefraction);
}

void Reflectogram::setIndexOfRefraction(LittleUInt32 ior)
{
    setValue<LittleUInt32Field>(ior,
                                MainBlock::FixedParameters,
                                FixedParametersBlock::IndexOfRefraction);
}

LittleUInt16 Reflectogram::backscatteringCoefficient() const
{
    return value<LittleUInt16Field>(MainBlock::FixedParameters,
                                    FixedParametersBlock::BackscatteringCoefficient);
}

void Reflectogram::setBackscatteringCoefficient(LittleUInt16 coef)
{
    setValue<LittleUInt16Field>(coef,
                                MainBlock::FixedParameters,
                                FixedParametersBlock::BackscatteringCoefficient);
}

LittleInt32 Reflectogram::fiberStartPosition() const
{
    return value<LittleInt32Field>(MainBlock::KeyEvents,
                                   KeyEventsBlock::FiberStartPosition);
}

void Reflectogram::setFiberStartPosition(LittleInt32 startPos)
{
    setValue<LittleInt32Field>(startPos,
                               MainBlock::KeyEvents,
                               KeyEventsBlock::FiberStartPosition);
}

LittleUInt16 Reflectogram::scalingFactor() const
{
    return value<LittleUInt16Field>(MainBlock::DataPoints,
                                    DataPointsBlock::ScalingFactor);
}

void Reflectogram::setScalingFactor(LittleUInt16 factor)
{
    setValue<LittleUInt16Field>(factor,
                                MainBlock::DataPoints,
                                DataPointsBlock::ScalingFactor);
}

LittleUInt16Vector Reflectogram::points() const
{
    return value<LittleUInt16VectorField>(MainBlock::DataPoints,
                                          DataPointsBlock::Points);
}

void Reflectogram::setPoints(LittleUInt16Vector points)
{
    setValue<LittleUInt16VectorField>(points,
                                      MainBlock::DataPoints,
                                      DataPointsBlock::Points);
}

template<class Field, class ...Ids>
typename Field::ValueType Reflectogram::value(Ids ...ids) const
{
    if (!m_mainBlock)
        return typename Field::ValueType();

    return m_mainBlock->descendant<Field>(ids...)->value();
}

template<class Field, class ...Ids>
void Reflectogram::setValue(const typename Field::ValueType &value, Ids ...ids)
{
    if (!m_mainBlock)
        return;

    m_mainBlock->descendant<Field>(ids...)->setValue(value);
}
