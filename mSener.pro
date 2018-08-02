#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T09:58:01
#
#-------------------------------------------------

QT       += core gui serialport sql

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
    serialPort/serialport.cpp \
    function/onesensor.cpp \
    function/doublesensor.cpp

HEADERS  += mainwindow.h \
    stopright.h \
    stopleft.h \
    menu.h \
    ccenter.h \
    function/maintab.h \
    serialPort/serialport.h \
    serialPort/serialconfiginfo.h \
    function/onesensor.h \
    function/doublesensor.h

FORMS    += mainwindow.ui \
    stopright.ui \
    stopleft.ui \
    menu.ui \
    ccenter.ui \
    function/maintab.ui \
    function/onesensor.ui \
    function/doublesensor.ui

RESOURCES += \
    res.qrc
