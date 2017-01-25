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
    reflectogram/blocks/checksumblock.cpp \
    reflectogram/blocks/mapblock.cpp \
    reflectogram/fields/littleuint16vectorfield.cpp \
    reflectogram/fields/rawfield.cpp \
    reflectogram/fields/stringfield.cpp \
    reflectogram/block.cpp \
    reflectogram/node.cpp \
    reflectogram/reflectogram.cpp \
    reflectogram/blocks/generalparametersblock.cpp \
    reflectogram/blocks/supplierparametersblock.cpp \
    reflectogram/blocks/fixedparametersblock.cpp \
    reflectogram/blocks/keyeventsblock.cpp \
    reflectogram/blocks/datapointsblock.cpp \
    reflectogram/blocks/rawblock.cpp \
    reflectogram/blocks/mapitemblock.cpp \
    reflectogram/blocks/keyeventblock.cpp \
    reflectogram/blocks/mainblock.cpp \
    fileinputbuffer.cpp \
    reflectogrammodel.cpp \
    gui/label.cpp \
    gui/toallbutton.cpp \
    gui/reflectogramwidget.cpp \
    gui/filelistpanel.cpp \
    gui/mainwindow.cpp

HEADERS  += \ 
    reflectogram/blocks/checksumblock.h \
    reflectogram/blocks/mapblock.h \
    reflectogram/fields/intfield.h \
    reflectogram/fields/littleuint16vectorfield.h \
    reflectogram/fields/rawfield.h \
    reflectogram/fields/stringfield.h \
    reflectogram/abstractinputbuffer.h \
    reflectogram/block.h \
    reflectogram/definitions.h \
    reflectogram/field.h \
    reflectogram/node.h \
    reflectogram/reflectogram.h \
    reflectogram/blocks/generalparametersblock.h \
    reflectogram/blocks/supplierparametersblock.h \
    reflectogram/blocks/fixedparametersblock.h \
    reflectogram/blocks/keyeventsblock.h \
    reflectogram/blocks/linkparametersblock.h \
    reflectogram/blocks/datapointsblock.h \
    reflectogram/blocks/nettekotdr10block.h \
    reflectogram/blocks/rawblock.h \
    reflectogram/fields/fixedrawfield.h \
    reflectogram/blocks/mapitemblock.h \
    reflectogram/fields/fixedstringfield.h \
    reflectogram/blocks/keyeventblock.h \
    reflectogram/blocks/mainblock.h \
    reflectogram/blocks/mainblockchildid.h \
    fileinputbuffer.h \
    reflectogrammodel.h \
    gui/label.h \
    gui/toallbutton.h \
    gui/reflectogramwidget.h \
    gui/filelistpanel.h \
    gui/mainwindow.h

FORMS    += \
    gui/reflectogramwidget.ui \
    gui/filelistpanel.ui \
    gui/mainwindow.ui
