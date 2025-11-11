TEMPLATE = subdirs

SUBDIRS += lib/SituationsModel
SUBDIRS += plugin

plugin.depends = lib/SituationsModel

OTHER_FILES += \
    .gitignore \
    CMakeLists.txt \
    AUTHORS \
    LICENSE \
    README.md \
