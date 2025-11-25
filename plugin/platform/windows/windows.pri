CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../lib/SituationsModel/debug

    LIBS += -L$$OUT_PWD/../../xylitol/lib/Xylitol/debug -lXylitold
    LIBS += -L$$OUT_PWD/../lib/SituationsModel/debug -lSituationsModeld
}
CONFIG(release, debug|release) {
    DESTDIR = $$OUT_PWD/../lib/SituationsModel/release

    LIBS += -L$$OUT_PWD/../../xylitol/lib/Xylitol/release -lXylitol
    LIBS += -L$$OUT_PWD/../lib/SituationsModel/release -lSituationsModel
}
