#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T09:58:01
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mSener
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stopright.cpp \
    stopleft.cpp \
    menu.cpp \
    ccenter.cpp \
    function/maintab.cpp \
    serialPort/serialport.cpp

HEADERS  += mainwindow.h \
    stopright.h \
    stopleft.h \
    menu.h \
    ccenter.h \
    function/maintab.h \
    serialPort/serialport.h \
    serialPort/serialconfiginfo.h

FORMS    += mainwindow.ui \
    stopright.ui \
    stopleft.ui \
    menu.ui \
    ccenter.ui \
    function/maintab.ui

RESOURCES += \
    res.qrc
