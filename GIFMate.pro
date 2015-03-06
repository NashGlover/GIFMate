#-------------------------------------------------
#
# Project created by QtCreator 2014-05-10T18:35:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GIFMate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    playthread.cpp

HEADERS  += mainwindow.h \
    playthread.h

FORMS    += mainwindow.ui

win32 {
        INCLUDEPATH += C:/OpenCV/opencv/build/include
        INCLUDEPATH += D:/ffmpeg-20141125-git-d0879a9-win32-dev/include
        INCLUDEPATH += D/
        LIBS += -LC:/OpenCV/opencv/build/x64/vc11/bin
        LIBS += -LC:/OpenCV/opencv/build/x64/vc11/lib
        LIBS += -lopencv_core249d -lopencv_highgui249d -lopencv_imgproc249d
}
