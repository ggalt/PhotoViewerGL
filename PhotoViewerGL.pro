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
    imageFrame.cpp \
    scaledImage.cpp

HEADERS  += \
    photowindow.h \
    imageFrame.h \
    scaledImage.h

FORMS    +=

RESOURCES += \
    photoviewerglresources.qrc
