DESTDIR = qml/$$replace(uri, \., /)

LIBS += -L$$OUT_PWD/../../xylitol/lib/Xylitol -lXylitol
LIBS += -L$$OUT_PWD/../lib/SituationsModel -lSituationsModel
QMAKE_LFLAGS += -Wl,-rpath,../../../../..:$$OUT_PWD/../lib

qmldir.files = $$PWD/../lib/SituationsModel/qmldir
qmldir.path = /usr/share/$${HARBOUR_NAME}/$${DESTDIR}
target.path = /usr/share/$${HARBOUR_NAME}/$${DESTDIR}
INSTALLS += qmldir target
