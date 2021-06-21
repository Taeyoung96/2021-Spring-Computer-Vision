#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T17:12:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = homework
TEMPLATE = app


SOURCES += main.cpp\
        mainframe.cpp \
    imageform.cpp \
    kfc.cpp \
    taeyoungcv.cpp

HEADERS  += mainframe.h \
    imageform.h \
    kfc.h \
    taeyoungcv.h

FORMS    += mainframe.ui \
    imageform.ui

RESOURCES += \
    images/mainframe.qrc
