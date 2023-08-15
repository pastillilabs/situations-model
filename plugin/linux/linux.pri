DESTDIR = qml/$$replace(uri, \., /)

LIBS += -L$$OUT_PWD/../../xylitol/lib -lxylitol
LIBS += -L$$OUT_PWD/../lib -lsituationsmodel
QMAKE_LFLAGS += -Wl,-rpath,../../../..:$$OUT_PWD/../lib
