TEMPLATE = subdirs

SUBDIRS = \
    lib \
    plugin \

plugin.depends = lib

OTHER_FILES += \
    .gitignore \
    AUTHORS \
    LICENSE \
    README.md \
