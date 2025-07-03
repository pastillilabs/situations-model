TEMPLATE = subdirs

SUBDIRS = lib/SituationsModel

lessThan(QT_MAJOR_VERSION, 6) {
    SUBDIRS += plugin

    plugin.depends = lib/SituationsModel
}

OTHER_FILES += \
    .gitignore \
    AUTHORS \
    LICENSE \
    README.md \
