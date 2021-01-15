#-------------------------------------------------
#
# Project created by QtCreator 2018-12-15T13:36:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app

CONFIG += c++1z

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        levenshteindistance.cpp \
        File.cpp \
        Project.cpp \
        main.cpp \
        mainwindow.cpp \
        prepare.cpp \
        nxndialog.cpp

HEADERS += \
        levenshteindistance.h \
        mainwindow.h \
        prepare.h \
        File.h \
        Project.h \
        nxndialog.h

FORMS += \
        mainwindow.ui \
        nxndialog.ui

DISTFILES += \
    cppkeywords.txt
