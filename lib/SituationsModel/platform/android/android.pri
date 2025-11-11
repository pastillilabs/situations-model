DEFINES += PLUGIN_FILE_TEMPLATE='\\"libSituations%1_$${QT_ARCH}.so\\"'

LIBS += -L$$OUT_PWD/../../../xylitol/lib/Xylitol -lXylitol_$${QT_ARCH}

target.path = /libs/$${ANDROID_TARGET_ARCH}
INSTALLS += target
