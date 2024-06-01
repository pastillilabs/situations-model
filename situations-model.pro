TEMPLATE = subdirs

SUBDIRS = lib

lessThan(QT_MAJOR_VERSION, 6) {
    SUBDIRS += plugin

    plugin.depends = lib
}

OTHER_FILES += \
    .gitignore \
    AUTHORS \
    LICENSE \
    README.md \
