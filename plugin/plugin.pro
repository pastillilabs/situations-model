uri = com.pastillilabs.situations.model

TEMPLATE = lib
TARGET = $$qtLibraryTarget(situationsmodelplugin)

QT += qml quick
CONFIG += plugin

QML_IMPORT_PATH += $$OUT_PWD/qml

INCLUDEPATH += $$PWD/../lib/include ../../xylitol/lib/include
DEPENDPATH += $$PWD/../lib/include ../../xylitol/lib/include

HEADERS += $$files($$PWD/*.h)
SOURCES += $$files($$PWD/*.cpp)

DISTFILES = qmldir

android: include(android/android.pri)
sailfish: include(sailfish/sailfish.pri)
win32: include(win/win.pri)
linux_desktop: include(linux/linux.pri)

# Copy qmldir to output directory
copy_qmldir.files = qmldir
copy_qmldir.path = $$DESTDIR
COPIES += copy_qmldir
