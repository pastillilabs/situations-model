DESTDIR = qml/SituationsModel

LIBS += -L$$OUT_PWD/../../xylitol/lib/Xylitol -lXylitol
LIBS += -L$$OUT_PWD/../lib/SituationsModel -lSituationsModel
QMAKE_LFLAGS += -Wl,-rpath,../../../../..:$$OUT_PWD/../lib

target.path = /usr/share/$${HARBOUR_NAME}/$${DESTDIR}
INSTALLS += target
