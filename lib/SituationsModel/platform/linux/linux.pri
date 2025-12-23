DISTFILES = $$PWD/../../qmldir

LIBS += -L$$OUT_PWD/../../../xylitol/lib/Xylitol -lXylitol

# Copy qml to output directory
copy_qml.files = $$files($$PWD/../../*.qml) $$PWD/../../qmldir
copy_qml.path = $$OUT_PWD
COPIES += copy_qml
