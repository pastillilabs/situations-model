DESTDIR = qml/$$replace(uri, \., /)

LIBS += -L$$OUT_PWD/../../xylitol/lib -lxylitol_$${QT_ARCH}
LIBS += -L$$OUT_PWD/../lib -lsituationsmodel_$${QT_ARCH}
