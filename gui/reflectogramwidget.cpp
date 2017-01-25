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

void ReflectogramWidget::setupItemModel(ReflectogramModel *model, int section,
                                        QWidget *editor, Label *label, ToAllButton *button)
{
    label->setModel(model);
    label->setSection(section);

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

    setupItemModel(model, ReflectogramModel::FilePathColumn,
                   ui->filePathEdit, ui->filePathLabel);

    setupItemModel(model, ReflectogramModel::SupplierNameColumn,
                   ui->supplierNameEdit, ui->supplierNameLabel, ui->supplierNameAllBtn);

    setupItemModel(model, ReflectogramModel::OtdrNameColumn,
                   ui->otdrNameEdit, ui->otdrNameLabel, ui->otdrNameAllBtn);

    setupItemModel(model, ReflectogramModel::OtdrSerialNumberColumn,
                   ui->otdrSerialNumberEdit, ui->otdrSerialNumberLabel, ui->otdrSerialNumberAllBtn);

    setupItemModel(model, ReflectogramModel::ModuleNameColumn,
                   ui->moduleNameEdit, ui->moduleNameLabel, ui->moduleNameAllBtn);

    setupItemModel(model, ReflectogramModel::ModuleSerialNumberColumn,
                   ui->moduleSerialNumberEdit, ui->moduleSerialNumberLabel, ui->moduleSerialNumberAllBtn);

    setupItemModel(model, ReflectogramModel::SoftwareVersionColumn,
                   ui->softwareVersionEdit, ui->softwareVersionLabel, ui->softwareVersionAllBtn);

    setupItemModel(model, ReflectogramModel::SupplierOtherColumn,
                   ui->supplierOtherEdit, ui->supplierOtherLabel, ui->supplierOtherAllBtn);

    setupItemModel(model, ReflectogramModel::DateTimeColumn,
                   ui->dateTimeEdit, ui->dateTimeLabel, ui->dateTimeAllBtn);

    setupItemModel(model, ReflectogramModel::WavelengthColumn,
                   ui->wavelengthEdit, ui->wavelengthLabel, ui->wavelengthAllBtn);

    setupItemModel(model, ReflectogramModel::PulseWidthColumn,
                   ui->pulseWidthEdit, ui->pulseWidthLabel, ui->pulseWidthAllBtn);

    setupItemModel(model, ReflectogramModel::SampleSpacingColumn,
                   ui->sampleSpacingEdit, ui->sampleSpacingLabel, ui->sampleSpacingAllBtn);

    setupItemModel(model, ReflectogramModel::IndexOfRefractionColumn,
                   ui->indexOfRefractionEdit, ui->indexOfRefractionLabel, ui->indexOfRefractionAllBtn);

    setupItemModel(model, ReflectogramModel::BackscatteringCoefficientColumn,
                   ui->backscatteringCoefficientEdit, ui->backscatteringCoefficientLabel,
                   ui->backscatteringCoefficientAllBtn);

    setupItemModel(model, ReflectogramModel::FiberStartPositionColumn,
                   ui->fiberStartPositionEdit, ui->fiberStartPositionLabel, ui->fiberStartPositionAllBtn);
}
