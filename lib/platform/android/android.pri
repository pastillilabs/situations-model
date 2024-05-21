INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

DEFINES += PLUGIN_FILE_TEMPLATE='\\"libsituations2%1_$${QT_ARCH}.so\\"'

SOURCES += $$files($$PWD/*.cpp, true)

LIBS += -L$$OUT_PWD/../../xylitol/lib -lxylitol_$${QT_ARCH}

target.path = /libs/$${ANDROID_TARGET_ARCH}
INSTALLS += target
