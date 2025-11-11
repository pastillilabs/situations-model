DESTDIR = qml/$$replace(uri, \., /)

LIBS += -L$$OUT_PWD/../lib/SituationsModel -lSituationsModel
LIBS += -L$$OUT_PWD/../../xylitol/lib/Xylitol -lXylitol
QMAKE_LFLAGS += -Wl,-rpath,../../../../..:$$OUT_PWD/../lib/SituationsModel:$$OUT_PWD/../../xylitol/lib/Xylitol
