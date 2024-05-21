INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

SOURCES += $$files($$PWD/*.cpp, true)

CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../../xylitol/lib/debug -lxylitold
}

CONFIG(release, debug|release) {
    LIBS += -L$$OUT_PWD/../../xylitol/lib/release -lxylitol
}
