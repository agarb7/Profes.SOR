#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T21:21:46
#
#-------------------------------------------------

QT       += core gui charts

CONFIG(release, debug|release): DEFINES += NDEBUG

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Professor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
    core/blocks/checksumblock.cpp \
    core/blocks/mapblock.cpp \
    core/fields/littleuint16vectorfield.cpp \
    core/fields/rawfield.cpp \
    core/fields/stringfield.cpp \
    core/block.cpp \
    core/node.cpp \
    core/reflectogram.cpp \
    core/blocks/generalparametersblock.cpp \
    core/blocks/supplierparametersblock.cpp \
    core/blocks/fixedparametersblock.cpp \
    core/blocks/keyeventsblock.cpp \
    core/blocks/datapointsblock.cpp \
    core/blocks/rawblock.cpp \
    core/blocks/mapitemblock.cpp \
    core/blocks/mainblock.cpp \
    model/fileinputbuffer.cpp \
    gui/label.cpp \
    gui/toallbutton.cpp \
    gui/reflectogramwidget.cpp \
    gui/filelistpanel.cpp \
    gui/mainwindow.cpp \
    core/blocks/keyeventsitemblock.cpp \
    model/columnmap.cpp \
    model/columns/samplespacingmetercolumn.cpp \
    model/reflectogram_.cpp \
    model/columns/pointscolumn.cpp \
    utils/objectpropertymapping.cpp \
    utils/datapropertymapper.cpp \
    utils/detail/modelsectionobject.cpp \
    utils/detail/common.cpp \
    gui/traceview.cpp \
    gui/tracechart.cpp \
    gui/traceselectionitem.cpp \
    gui/traceseries.cpp

HEADERS  += \ 
    core/blocks/checksumblock.h \
    core/blocks/mapblock.h \
    core/fields/intfield.h \
    core/fields/littleuint16vectorfield.h \
    core/fields/rawfield.h \
    core/fields/stringfield.h \
    core/abstractinputbuffer.h \
    core/block.h \
    core/field.h \
    core/node.h \
    core/reflectogram.h \
    core/blocks/generalparametersblock.h \
    core/blocks/supplierparametersblock.h \
    core/blocks/fixedparametersblock.h \
    core/blocks/keyeventsblock.h \
    core/blocks/linkparametersblock.h \
    core/blocks/datapointsblock.h \
    core/blocks/nettekotdr10block.h \
    core/blocks/rawblock.h \
    core/fields/fixedrawfield.h \
    core/blocks/mapitemblock.h \
    core/fields/fixedstringfield.h \
    core/blocks/mainblock.h \
    model/fileinputbuffer.h \
    gui/label.h \
    gui/toallbutton.h \
    gui/reflectogramwidget.h \
    gui/filelistpanel.h \
    gui/mainwindow.h \
    core/mappingblock.h \
    core/blocks/mainchildid.h \
    core/blocks/keyeventsitemblock.h \
    core/types.h \
    core/mptypes.h \
    model/abstractcolumn.h \
    model/columns/typedcolumn.h \
    model/columns/intcolumn.h \
    model/columns/stringcolumn.h \
    model/columns/doublecolumn.h \
    model/columnmap.h \
    model/columns/datetimecolumn.h \
    model/columns/pointscolumn.h \
    model/columns/samplespacingmetercolumn.h \
    model/reflectogramcolumn.h \
    model/reflectogram_.h \
    model/types_.h \
    utils/objectpropertymapping.h \
    utils/datapropertymapper.h \
    utils/detail/modelsectionobject.h \
    utils/detail/common.h \
    gui/traceview.h \
    gui/tracechart.h \
    gui/traceselectionitem.h \
    gui/traceseries.h

FORMS    += \
    gui/reflectogramwidget.ui \
    gui/filelistpanel.ui \
    gui/mainwindow.ui
