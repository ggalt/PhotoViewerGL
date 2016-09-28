#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T14:27:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhotoViewerGL
TEMPLATE = app


SOURCES += main.cpp\
    photowindow.cpp \
    animatedimage.cpp \
    photoframe.cpp \
    scaledimage.cpp

HEADERS  += \
    photowindow.h \
    animatedimage.h \
    photoframe.h \
    scaledimage.h

FORMS    +=

RESOURCES += \
    photoviewerglresources.qrc
