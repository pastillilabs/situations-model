CONFIG(debug, debug|release) {
    DESTDIR = debug/qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../../xylitol/lib/debug -lxylitold
    LIBS += -L$$OUT_PWD/../lib/debug -lsituationsmodeld
}
CONFIG(release, debug|release) {
    DESTDIR = release/qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../../xylitol/lib/release -lxylitol
    LIBS += -L$$OUT_PWD/../lib/release -lsituationsmodel
}
