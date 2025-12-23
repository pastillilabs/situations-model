QT += qml

TEMPLATE = lib

TARGET = $$qtLibraryTarget(SituationsModel)

CONFIG += plugin qmltypes
DEFINES += MODEL_LIBRARY

QML_IMPORT_NAME = SituationsModel
QML_IMPORT_MAJOR_VERSION = 1

INCLUDEPATH += $$PWD/include
INCLUDEPATH += ../../../xylitol/lib/Xylitol/include

DEPENDPATH += $$PWD/include
DEPENDPATH += ../../../xylitol/lib/Xylitol/include

# Needed for qmltypes
INCLUDEPATH += $$PWD/include/SituationsModel
DEPENDPATH += $$PWD/include/SituationsModel

HEADERS += $$files($$PWD/include/SituationsModel/*.h)
HEADERS += $$files($$PWD/src/*.h)
SOURCES += $$files($$PWD/src/*.cpp)

include(platform/platform.pri)
