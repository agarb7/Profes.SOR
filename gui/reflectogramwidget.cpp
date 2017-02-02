#include "reflectogramwidget.h"
#include "ui_reflectogramwidget.h"

#include "model/reflectogram_.h"

ReflectogramWidget::ReflectogramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReflectogramWidget)
{
    ui->setupUi(this);

    connect(ui->traceHorZoom, &QAbstractSlider::valueChanged, [this](int value) {
        double factor = 1;

        if (value != 0) {
            factor = value>0
                    ? value+1
                    : 1./(-value+1);
        }

        ui->traceEdit->setHorizontalZoom(factor);
    });

    connect(ui->traceHorScroll, &QAbstractSlider::valueChanged, [this](int value) {
        double min = ui->traceHorScroll->minimum();
        double max = ui->traceHorScroll->maximum();
        double cur = value;

        double part = (cur-min)/(max-min);

        ui->traceEdit->horizontalScrollTo(part);
    });
}

ReflectogramWidget::~ReflectogramWidget()
{
    delete ui;
}

void ReflectogramWidget::setCurrentIndex(int index)
{    
    m_mapper.setCurrentIndex(index);
}

Model::Reflectogram *ReflectogramWidget::model() const
{
    return static_cast<Model::Reflectogram*>(m_mapper.model());
}

void ReflectogramWidget::setModel(Model::Reflectogram *model)
{
    using Model::ReflectogramColumn;

    m_mapper.setModel(model);    

    setupItemModel(model, ReflectogramColumn::FilePath,
                   ui->filePathEdit, ui->filePathLabel);

    setupItemModel(model, ReflectogramColumn::SupplierName,
                   ui->supplierNameEdit, ui->supplierNameLabel, ui->supplierNameAllBtn);

    setupItemModel(model, ReflectogramColumn::OtdrName,
                   ui->otdrNameEdit, ui->otdrNameLabel, ui->otdrNameAllBtn);

    setupItemModel(model, ReflectogramColumn::OtdrSerialNumber,
                   ui->otdrSerialNumberEdit, ui->otdrSerialNumberLabel, ui->otdrSerialNumberAllBtn);

    setupItemModel(model, ReflectogramColumn::ModuleName,
                   ui->moduleNameEdit, ui->moduleNameLabel, ui->moduleNameAllBtn);

    setupItemModel(model, ReflectogramColumn::ModuleSerialNumber,
                   ui->moduleSerialNumberEdit, ui->moduleSerialNumberLabel, ui->moduleSerialNumberAllBtn);

    setupItemModel(model, ReflectogramColumn::SoftwareVersion,
                   ui->softwareVersionEdit, ui->softwareVersionLabel, ui->softwareVersionAllBtn);

    setupItemModel(model, ReflectogramColumn::SupplierOther,
                   ui->supplierOtherEdit, ui->supplierOtherLabel, ui->supplierOtherAllBtn);

    setupItemModel(model, ReflectogramColumn::DateTime,
                   ui->dateTimeEdit, ui->dateTimeLabel, ui->dateTimeAllBtn);

    setupItemModel(model, ReflectogramColumn::Wavelength,
                   ui->wavelengthEdit, ui->wavelengthLabel, ui->wavelengthAllBtn);

    setupItemModel(model, ReflectogramColumn::PulseWidth,
                   ui->pulseWidthEdit, ui->pulseWidthLabel, ui->pulseWidthAllBtn);

    setupItemModel(model, ReflectogramColumn::SampleSpacing,
                   ui->sampleSpacingEdit, ui->sampleSpacingLabel, ui->sampleSpacingAllBtn);

    setupItemModel(model, ReflectogramColumn::IndexOfRefraction,
                   ui->indexOfRefractionEdit, ui->indexOfRefractionLabel, ui->indexOfRefractionAllBtn);

    setupItemModel(model, ReflectogramColumn::BackscatteringCoefficient,
                   ui->backscatteringCoefficientEdit, ui->backscatteringCoefficientLabel,
                   ui->backscatteringCoefficientAllBtn);

    setupItemModel(model, ReflectogramColumn::FiberStartPosition,
                   ui->fiberStartPositionEdit, ui->fiberStartPositionLabel, ui->fiberStartPositionAllBtn);

    setupItemModel(model, ReflectogramColumn::SampleSpacingMeter,
                   ui->sampleSpacingMeterEdit);

    setupTraceEditModel(model);
}

void ReflectogramWidget::setupItemModel(Model::Reflectogram *model, Model::ReflectogramColumn columnId,
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

void ReflectogramWidget::setupTraceEditModel(Model::Reflectogram */*model*/)
{
    m_mapper.addMapping(ui->traceEdit,
                        int(Model::ReflectogramColumn::Points));

    ui->traceEdit->setSampleSpacing(5.10);

//    m_mapper.addMapping(ui->traceEdit,
//                        int(Model::ReflectogramColumn::SampleSpacingMeter),
//                        "sampleSpacing");
}
