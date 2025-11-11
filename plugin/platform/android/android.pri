DESTDIR = qml/$$replace(uri, \., /)

LIBS += -L$$OUT_PWD/../../xylitol/lib/Xylitol -lXylitol_$${QT_ARCH}
LIBS += -L$$OUT_PWD/../lib/SituationsModel -lSituationsModel_$${QT_ARCH}
