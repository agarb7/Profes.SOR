#include "reflectogram.h"

#include "blocks/supplierparametersblock.h"
#include "blocks/fixedparametersblock.h"
#include "blocks/keyeventsblock.h"
#include "blocks/datapointsblock.h"
#include "blocks/checksumblock.h"

#include "fields/stringfield.h"
#include "fields/intfield.h"
#include "fields/littleuint16vectorfield.h"

#include <type_traits>

namespace Core {

bool Reflectogram::read(AbstractInputBuffer &buffer)
{
    m_mainBlock.reset(new MainBlock);

    if (!m_mainBlock->readChildren(buffer)) {
        m_mainBlock.reset();
        return false;
    }

    return true;
}

bool Reflectogram::empty() const
{
    return !m_mainBlock;
}

void Reflectogram::clear()
{
    m_mainBlock.reset();
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
            = m_mainBlock->child<Main::Checksum>();

    chksum->calculate(m_mainBlock->dataBegin(), m_mainBlock->dataIterator(chksum));
}

String Reflectogram::supplierName() const
{
    return value<SupplierName>();
}

void Reflectogram::setSupplierName(const String &name)
{
    setValue<SupplierName>(name);
}

String Reflectogram::otdrName() const
{
    return value<OtdrName>();
}

void Reflectogram::setOtdrName(const String &name)
{
    setValue<OtdrName>(name);
}

String Reflectogram::otdrSerialNumber() const
{
    return value<OtdrSerialNumber>();
}

void Reflectogram::setOtdrSerialNumber(const String &sn)
{
    setValue<OtdrSerialNumber>(sn);
}

String Reflectogram::moduleName() const
{
    return value<ModuleName>();
}

void Reflectogram::setModuleName(const String &name)
{
    setValue<ModuleName>(name);
}

String Reflectogram::moduleSerialNumber() const
{
    return value<ModuleSerialNumber>();
}

void Reflectogram::setModuleSerialNumber(const String &sn)
{
    setValue<ModuleSerialNumber>(sn);
}

String Reflectogram::softwareVersion() const
{
    return value<SoftwareVersion>();
}

void Reflectogram::setSoftwareVersion(const String &version)
{
    setValue<SoftwareVersion>(version);
}

String Reflectogram::supplierOther() const
{
    return value<SupplierOther>();
}

void Reflectogram::setSupplierOther(const String &other)
{
    setValue<SupplierOther>(other);
}

LeUInt32 Reflectogram::dateTime() const
{
    return value<DateTime>();
}

void Reflectogram::setDateTime(LeUInt32 dateTime)
{
    setValue<DateTime>(dateTime);
}

LeUInt16 Reflectogram::wavelength() const
{
    return value<Wavelength>();
}

void Reflectogram::setWavelength(LeUInt16 wavelength)
{
    setValue<Wavelength>(wavelength);
}

LeUInt16 Reflectogram::pulseWidth() const
{
    return value<PulseWidth>();
}

void Reflectogram::setPulseWidth(LeUInt16 pulseWidth)
{
    setValue<PulseWidth>(pulseWidth);
}

LeUInt32 Reflectogram::sampleSpacing() const
{
    return value<SampleSpacing>();
}

void Reflectogram::setSampleSpacing(LeUInt32 spacing)
{
    setValue<SampleSpacing>(spacing);
}

LeUInt32 Reflectogram::indexOfRefraction() const
{
    return value<IndexOfRefraction>();
}

void Reflectogram::setIndexOfRefraction(LeUInt32 ior)
{
    setValue<IndexOfRefraction>(ior);
}

LeUInt16 Reflectogram::backscatteringCoefficient() const
{
    return value<BackscatteringCoefficient>();
}

void Reflectogram::setBackscatteringCoefficient(LeUInt16 coef)
{
    setValue<BackscatteringCoefficient>(coef);
}

LeInt32 Reflectogram::fiberStartPosition() const
{
    return value<FiberStartPosition>();
}

void Reflectogram::setFiberStartPosition(LeInt32 startPos)
{
    setValue<FiberStartPosition>(startPos);
}

LeUInt16 Reflectogram::scalingFactor() const
{
    return value<ScalingFactor>();
}

void Reflectogram::setScalingFactor(LeUInt16 factor)
{
    setValue<ScalingFactor>(factor);
}

LeUInt16Vector Reflectogram::points() const
{
    return value<Points>();
}

void Reflectogram::setPoints(LeUInt16Vector points)
{
    setValue<Points>(points);
}

} // namespace Core
