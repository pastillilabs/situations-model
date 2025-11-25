CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../../../xylitol/lib/Xylitol/debug -lXylitold

    # Copy qml to output directory
    copy_qml.files = $$files($$PWD/../../*.qml) $$PWD/../../qmldir
    copy_qml.path = $$OUT_PWD/debug
}

CONFIG(release, debug|release) {
    LIBS += -L$$OUT_PWD/../../../xylitol/lib/Xylitol/release -lXylitol

    # Copy qml to output directory
    copy_qml.files = $$files($$PWD/../../*.qml) $$PWD/../../qmldir
    copy_qml.path = $$OUT_PWD/release
}

COPIES += copy_qml
