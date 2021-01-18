TEMPLATE = subdirs

SUBDIRS += \
    app \
    tests \
    utils

cli.depends = utils
gui.depends = utils
tests.depends = utils

