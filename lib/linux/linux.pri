INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

SOURCES += \
    $$files($$PWD/*.cpp, true)

LIBS += -L$$OUT_PWD/../../xylitol/lib -lxylitol
