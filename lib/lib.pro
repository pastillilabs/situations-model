TEMPLATE = lib
TARGET = $$qtLibraryTarget(situationsmodel)

CONFIG += plugin
greaterThan(QT_MAJOR_VERSION, 5) {
    CONFIG += qmltypes
}
DEFINES += MODEL_LIBRARY

greaterThan(QT_MAJOR_VERSION, 5) {
    QML_IMPORT_NAME = com.pastillilabs.situations.model
    QML_IMPORT_MAJOR_VERSION = 1
}

INCLUDEPATH += $$PWD/include ../../xylitol/lib/include
DEPENDPATH += $$PWD/include ../../xylitol/lib/include

greaterThan(QT_MAJOR_VERSION, 5) {
    # Needed for moc
    INCLUDEPATH += $$PWD/include/situations-model
    DEPENDPATH += $$PWD/include/situations-model
}

HEADERS += $$files($$PWD/include/situations-model/*.h, true)
HEADERS += $$files($$PWD/src/*.h, true)
SOURCES += $$files($$PWD/src/*.cpp, true)

include(platform/platform.pri)
