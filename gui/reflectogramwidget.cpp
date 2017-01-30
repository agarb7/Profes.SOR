#include "reflectogramwidget.h"
#include "ui_reflectogramwidget.h"

#include "model/reflectogrammodel.h"

ReflectogramWidget::ReflectogramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReflectogramWidget)
{
    ui->setupUi(this);
}

ReflectogramWidget::~ReflectogramWidget()
{
    delete ui;
}

void ReflectogramWidget::setCurrentIndex(int index)
{    
    m_mapper.setCurrentIndex(index);
}

void ReflectogramWidget::setupItemModel(ReflectogramModel *model, ReflectogramModelColumn columnId,
                                        QWidget *editor, Label *label, ToAllButton *button)
{
    int section = int(columnId);

    if (label) {
        label->setModel(model);
        label->setSection(section);
    }

    if (button) {
        button->setModel(model);
        button->setEditor(editor);
        button->setSection(section);
    }

    m_mapper.addMapping(editor, section);
}

ReflectogramModel *ReflectogramWidget::model() const
{
    return static_cast<ReflectogramModel*>(m_mapper.model());
}

void ReflectogramWidget::setModel(ReflectogramModel *model)
{
    m_mapper.setModel(model);    

    setupItemModel(model, ReflectogramModelColumn::FilePath,
                   ui->filePathEdit, ui->filePathLabel);

    setupItemModel(model, ReflectogramModelColumn::SupplierName,
                   ui->supplierNameEdit, ui->supplierNameLabel, ui->supplierNameAllBtn);

    setupItemModel(model, ReflectogramModelColumn::OtdrName,
                   ui->otdrNameEdit, ui->otdrNameLabel, ui->otdrNameAllBtn);

    setupItemModel(model, ReflectogramModelColumn::OtdrSerialNumber,
                   ui->otdrSerialNumberEdit, ui->otdrSerialNumberLabel, ui->otdrSerialNumberAllBtn);

    setupItemModel(model, ReflectogramModelColumn::ModuleName,
                   ui->moduleNameEdit, ui->moduleNameLabel, ui->moduleNameAllBtn);

    setupItemModel(model, ReflectogramModelColumn::ModuleSerialNumber,
                   ui->moduleSerialNumberEdit, ui->moduleSerialNumberLabel, ui->moduleSerialNumberAllBtn);

    setupItemModel(model, ReflectogramModelColumn::SoftwareVersion,
                   ui->softwareVersionEdit, ui->softwareVersionLabel, ui->softwareVersionAllBtn);

    setupItemModel(model, ReflectogramModelColumn::SupplierOther,
                   ui->supplierOtherEdit, ui->supplierOtherLabel, ui->supplierOtherAllBtn);

    setupItemModel(model, ReflectogramModelColumn::DateTime,
                   ui->dateTimeEdit, ui->dateTimeLabel, ui->dateTimeAllBtn);

    setupItemModel(model, ReflectogramModelColumn::Wavelength,
                   ui->wavelengthEdit, ui->wavelengthLabel, ui->wavelengthAllBtn);

    setupItemModel(model, ReflectogramModelColumn::PulseWidth,
                   ui->pulseWidthEdit, ui->pulseWidthLabel, ui->pulseWidthAllBtn);

    setupItemModel(model, ReflectogramModelColumn::SampleSpacing,
                   ui->sampleSpacingEdit, ui->sampleSpacingLabel, ui->sampleSpacingAllBtn);

    setupItemModel(model, ReflectogramModelColumn::IndexOfRefraction,
                   ui->indexOfRefractionEdit, ui->indexOfRefractionLabel, ui->indexOfRefractionAllBtn);

    setupItemModel(model, ReflectogramModelColumn::BackscatteringCoefficient,
                   ui->backscatteringCoefficientEdit, ui->backscatteringCoefficientLabel,
                   ui->backscatteringCoefficientAllBtn);

    setupItemModel(model, ReflectogramModelColumn::FiberStartPosition,
                   ui->fiberStartPositionEdit, ui->fiberStartPositionLabel, ui->fiberStartPositionAllBtn);

    setupItemModel(model, ReflectogramModelColumn::SampleSpacingMeter,
                   ui->sampleSpacingMeterEdit);

}
