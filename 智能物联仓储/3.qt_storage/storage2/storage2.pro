#-------------------------------------------------
#
# Project created by QtCreator 2019-11-02T11:16:30
#
#-------------------------------------------------

QT       += core gui sql network
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = storage2
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    set.cpp \
    sqldriver.cpp

HEADERS  += login.h \
    set.h \
    sqldriver.h

FORMS    += login.ui \
    set.ui

RESOURCES += \
    uImage/login.qrc \
    image.qrc
