#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T19:56:26
#
#-------------------------------------------------

QT       += core gui

QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IRCameraDemo
TEMPLATE = app
CONFIG   += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    util.cpp \
#    uvc/ircammanager.cpp \
#    uvc/v4l2core.c \
    udevhelper.c \

HEADERS  += mainwindow.h \
    util.h \
    uvc/ircammanager.h \
    uvc/v4l2core.h \
    udevhelper.h \

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv4 \
               /usr/local/include/opencv4/opencv2 \


LIBS += /usr/local/lib/libopencv_imgcodecs.so\
        /usr/local/lib/libopencv_core.so\
       /usr/local/lib/libopencv_highgui.so\
       /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_videoio.so\

unix:!macx: LIBS += -ludev

QMAKE_LFLAGS+= -no-pie

unix:!macx: LIBS += -L$$PWD/uvc/ -lv4l2

INCLUDEPATH += $$PWD/uvc
DEPENDPATH += $$PWD/uvc

unix:!macx: LIBS += -L$$PWD/uvc/ -lv4l2core

INCLUDEPATH += $$PWD/uvc
DEPENDPATH += $$PWD/uvc
