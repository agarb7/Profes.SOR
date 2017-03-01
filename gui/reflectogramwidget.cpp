#include "reflectogramwidget.h"
#include "ui_reflectogramwidget.h"

#include "traceselectionitem.h"

#include "model/reflectogram_.h"

#include "utils/objectpropertymapping.h"

ReflectogramWidget::ReflectogramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReflectogramWidget)
{
    ui->setupUi(this);

    ui->timeAllBtn->setReflectogramWidget(this);
    ui->traceSkewBtn->setSourceEditor(ui->traceSkewEdit);

    TraceSelectionItem *selection = ui->traceView->traceSelection();

    setupEditorMapping(selection, "start", ui->traceSelStartEdit);
    setupEditorMapping(selection, "end", ui->traceSelEndEdit);

    setupEditorMapping(ui->traceView, "horizontalResolution",
                       ui->traceHorizontalResolutionEdit);

    setupEditorMapping(ui->traceView, "verticalResolution",
                       ui->traceVerticalResolutionEdit);

    setupEditorMapping(ui->traceView, "useAll", ui->traceAllCheck);
}

ReflectogramWidget::~ReflectogramWidget()
{
    delete ui;
}

void ReflectogramWidget::setCurrentIndex(int index)
{    
    m_mapper.setCurrentIndex(index);    
    ui->traceView->setCurrentRow(index);
}

void ReflectogramWidget::setupEditorMapping(QObject *object, const QByteArray &objectProp,
                                            QWidget *editor)
{
    using Mapping = Utils::ObjectPropertyMapping;

    auto mapping = new Mapping(object, objectProp,
                               editor, editor->metaObject()->userProperty().name(),
                               Mapping::BothMapping, this);

    mapping->writeSecondProperty();
}

Model::Reflectogram *ReflectogramWidget::model() const
{
    return static_cast<Model::Reflectogram*>(m_mapper.model());
}

void ReflectogramWidget::setModel(Model::Reflectogram *model)
{
    using Model::ReflectogramColumn;

    m_mapper.setModel(model);
    ui->traceView->setModel(model);

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

    setupItemModel(model, ReflectogramColumn::Date,
                   ui->dateEdit, 0, ui->dateAllBtn);

    setupItemModel(model, ReflectogramColumn::Time,
                   ui->timeEdit, 0, ui->timeAllBtn);

    setupItemModel(model, ReflectogramColumn::Wavelength,
                   ui->wavelengthEdit, ui->wavelengthLabel, ui->wavelengthAllBtn);

    setupItemModel(model, ReflectogramColumn::PulseWidth,
                   ui->pulseWidthEdit, ui->pulseWidthLabel, ui->pulseWidthAllBtn);

    setupItemModel(model, ReflectogramColumn::SampleSpacing,
                   ui->sampleSpacingEdit, ui->sampleSpacingLabel, ui->sampleSpacingAllBtn);

    setupItemModel(model, ReflectogramColumn::SampleSpacingMeter,
                   ui->sampleSpacingMeterEdit);

    setupItemModel(model, ReflectogramColumn::IndexOfRefraction,
                   ui->indexOfRefractionEdit, ui->indexOfRefractionLabel, ui->indexOfRefractionAllBtn);

    setupItemModel(model, ReflectogramColumn::BackscatteringCoefficient,
                   ui->backscatteringCoefficientEdit, ui->backscatteringCoefficientLabel,
                   ui->backscatteringCoefficientAllBtn);

    setupItemModel(model, ReflectogramColumn::FiberStartPosition,
                   ui->fiberStartPositionEdit, ui->fiberStartPositionLabel, ui->fiberStartPositionAllBtn);

    setupItemModel(model, ReflectogramColumn::FiberLength,
                   ui->fiberLengthEdit, ui->fiberLengthLabel, ui->fiberLengthAllBtn);
}

int ReflectogramWidget::currentIndex() const
{
    return m_mapper.currentIndex();
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

    m_mapper.addMapping(section, editor);
}
