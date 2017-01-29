#ifndef REFLECTOGRAM_H
#define REFLECTOGRAM_H

#include "blocks/mainblock.h"

#include "types.h"

#include <memory>
#include <type_traits>

namespace Core {

class AbstractInputBuffer;

class Reflectogram
{
public:
    enum Field {
        SupplierName,
        OtdrName,
        OtdrSerialNumber,
        ModuleName,
        ModuleSerialNumber,
        SoftwareVersion,
        SupplierOther,
        DateTime,
        Wavelength,
        PulseWidth,
        SampleSpacing,
        IndexOfRefraction,
        BackscatteringCoefficient,
        FiberStartPosition,
        ScalingFactor,
        Points
    };

private:
    template <Field field, class ...Ics>
    using FieldMapItem = MplPair<Ic<Field, field>, MplVector<Ics...>>;

    using FieldMap = MplMap<
        FieldMapItem<
            SupplierName,
            Ic<Main, Main::SupplierParameters>,
            Ic<SupplierParameters, SupplierParameters::SupplierName>
        >,
        FieldMapItem<
            OtdrName,
            Ic<Main, Main::SupplierParameters>,
            Ic<SupplierParameters, SupplierParameters::OtdrName>
        >,
        FieldMapItem<
            OtdrSerialNumber,
            Ic<Main, Main::SupplierParameters>,
            Ic<SupplierParameters, SupplierParameters::OtdrSerialNumber>
        >,
        FieldMapItem<
            ModuleName,
            Ic<Main, Main::SupplierParameters>,
            Ic<SupplierParameters, SupplierParameters::ModuleName>
        >,
        FieldMapItem<
            ModuleSerialNumber,
            Ic<Main, Main::SupplierParameters>,
            Ic<SupplierParameters, SupplierParameters::ModuleSerialNumber>
        >,
        FieldMapItem<
            SoftwareVersion,
            Ic<Main, Main::SupplierParameters>,
            Ic<SupplierParameters, SupplierParameters::SoftwareVersion>
        >,
        FieldMapItem<
            SupplierOther,
            Ic<Main, Main::SupplierParameters>,
            Ic<SupplierParameters, SupplierParameters::Other>
        >,
        FieldMapItem<
            DateTime,
            Ic<Main, Main::FixedParameters>,
            Ic<FixedParameters, FixedParameters::DateTime>
        >,
        FieldMapItem<
            Wavelength,
            Ic<Main, Main::FixedParameters>,
            Ic<FixedParameters, FixedParameters::Wavelength>
        >,
        FieldMapItem<
            PulseWidth,
            Ic<Main, Main::FixedParameters>,
            Ic<FixedParameters, FixedParameters::PulseWidth>
        >,
        FieldMapItem<
            SampleSpacing,
            Ic<Main, Main::FixedParameters>,
            Ic<FixedParameters, FixedParameters::SampleSpacing>
        >,
        FieldMapItem<
            IndexOfRefraction,
            Ic<Main, Main::FixedParameters>,
            Ic<FixedParameters, FixedParameters::IndexOfRefraction>
        >,
        FieldMapItem<
            BackscatteringCoefficient,
            Ic<Main, Main::FixedParameters>,
            Ic<FixedParameters, FixedParameters::BackscatteringCoefficient>
        >,
        FieldMapItem<
            FiberStartPosition,
            Ic<Main, Main::KeyEvents>,
            Ic<KeyEvents, KeyEvents::FiberStartPosition>
        >,
        FieldMapItem<
            ScalingFactor,
            Ic<Main, Main::DataPoints>,
            Ic<DataPoints, DataPoints::ScalingFactor>
        >,
        FieldMapItem<
            Points,
            Ic<Main, Main::DataPoints>,
            Ic<DataPoints, DataPoints::Points>
        >
    >;

    template <Field field>
    using ValueType = typename DescendantNodeType<
        MplAt<FieldMap, Ic<Field, field>>
    >::ValueType;

    template <Field field>
    using Ics = MplAt<FieldMap, Ic<Field, field>>;

public:

    using DataIterator = Block::DataIterator;

    bool read(AbstractInputBuffer& buffer);

    bool empty() const;
    void clear();

    DataIterator dataBegin() const;
    DataIterator dataEnd() const;

    template <Field field>
    ValueType<field> value() const
    {
        if (!m_mainBlock)
            return ValueType<field>();

        return m_mainBlock
                ->descendant<Ics<field>>()
                ->value();
    }

    template <Field field>
    void setValue(const ValueType<field> &value)
    {
        if (!m_mainBlock)
            return;

        return m_mainBlock
                ->descendant<Ics<field>>()
                ->setValue(value);
    }

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

    String supplierOther() const;
    void setSupplierOther(const String &other);

    LeUInt32 dateTime() const;
    void setDateTime(LeUInt32 dateTime);

    LeUInt16 wavelength() const;
    void setWavelength(LeUInt16 wavelength);

    LeUInt16 pulseWidth() const;
    void setPulseWidth(LeUInt16 pulseWidth);

    LeUInt32 sampleSpacing() const;
    void setSampleSpacing(LeUInt32 spacing);

    LeUInt32 indexOfRefraction() const;
    void setIndexOfRefraction(LeUInt32 ior);

    LeUInt16 backscatteringCoefficient() const;
    void setBackscatteringCoefficient(LeUInt16 coef);

    LeInt32 fiberStartPosition() const;
    void setFiberStartPosition(LeInt32 startPos);

    LeUInt16 scalingFactor() const;
    void setScalingFactor(LeUInt16 factor);

    LeUInt16Vector points() const;
    void setPoints(LeUInt16Vector points);

private:
    std::unique_ptr<MainBlock> m_mainBlock;
};

} // namespace Core

#endif // REFLECTOGRAM_H
