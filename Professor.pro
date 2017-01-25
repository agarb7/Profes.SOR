#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T21:21:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Profestsor
TEMPLATE = app

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
    core/blocks/keyeventblock.cpp \
    core/blocks/mainblock.cpp \
    model/fileinputbuffer.cpp \
    model/reflectogrammodel.cpp \
    gui/label.cpp \
    gui/toallbutton.cpp \
    gui/reflectogramwidget.cpp \
    gui/filelistpanel.cpp \
    gui/mainwindow.cpp

HEADERS  += \ 
    core/blocks/checksumblock.h \
    core/blocks/mapblock.h \
    core/fields/intfield.h \
    core/fields/littleuint16vectorfield.h \
    core/fields/rawfield.h \
    core/fields/stringfield.h \
    core/abstractinputbuffer.h \
    core/block.h \
    core/definitions.h \
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
    core/blocks/keyeventblock.h \
    core/blocks/mainblock.h \
    core/blocks/mainblockchildid.h \
    model/fileinputbuffer.h \
    model/reflectogrammodel.h \
    gui/label.h \
    gui/toallbutton.h \
    gui/reflectogramwidget.h \
    gui/filelistpanel.h \
    gui/mainwindow.h

FORMS    += \
    gui/reflectogramwidget.ui \
    gui/filelistpanel.ui \
    gui/mainwindow.ui
