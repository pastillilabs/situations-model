uri = SituationsModel

TEMPLATE = lib

TARGET = $$qtLibraryTarget(SituationsModelPlugin)

QT += qml quick
CONFIG += plugin

QML_IMPORT_PATH += $$OUT_PWD/qml

INCLUDEPATH += $$PWD/../lib/SituationsModel/include
INCLUDEPATH += ../../xylitol/lib/Xylitol/include

DEPENDPATH += $$PWD/../lib/SituationsModel/include
DEPENDPATH += ../../xylitol/lib/Xylitol/include

HEADERS += $$files($$PWD/src/*.h)
SOURCES += $$files($$PWD/src/*.cpp)

include(platform/platform.pri)

# Copy qml to output directory
copy_qml.files = $$PWD/../lib/SituationsModel/qmldir
copy_qml.path = $$DESTDIR
COPIES += copy_qml
