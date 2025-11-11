CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../../../xylitol/lib/Xylitol/debug -lXylitold
}

CONFIG(release, debug|release) {
    LIBS += -L$$OUT_PWD/../../../xylitol/lib/Xylitol/release -lXylitol
}
