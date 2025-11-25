LIBS += -L$$OUT_PWD/../../../xylitol/lib/Xylitol -lXylitol

qmldir.files = qmldir
qmldir.path = /usr/share/$${HARBOUR_NAME}/qml/SituationsModel
target.path = /usr/share/$${HARBOUR_NAME}/lib
INSTALLS += qmldir target
