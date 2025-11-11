CONFIG(debug, debug|release) {
    DESTDIR = debug/qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../../Xylitol/lib/Xylitol/debug -lXylitold
    LIBS += -L$$OUT_PWD/../lib/SituationsModel/debug -lSituationsModeld
}
CONFIG(release, debug|release) {
    DESTDIR = release/qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../../xylitol/lib/Xylitol/release -lXylitol
    LIBS += -L$$OUT_PWD/../lib/SituationsModel/release -lSituationsModel
}
