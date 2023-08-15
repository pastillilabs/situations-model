TEMPLATE = lib
TARGET = $$qtLibraryTarget(situationsmodel)

CONFIG += plugin
DEFINES += MODEL_LIBRARY

INCLUDEPATH += $$PWD/include ../../xylitol/lib/include
DEPENDPATH += $$PWD/include ../../xylitol/lib/include

HEADERS += $$files($$PWD/include/model/*.h, true)
HEADERS += $$files($$PWD/src/*.h, true)
SOURCES += $$files($$PWD/src/*.cpp, true)

android: include(android/android.pri)
sailfish: include(sailfish/sailfish.pri)
win32: include(win/win.pri)
linux_desktop: include(linux/linux.pri)
