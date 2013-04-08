#-------------------------------------------------
#
# Project created by QtCreator 2013-04-01T14:06:41
#
#-------------------------------------------------

QT       += core gui\
            testlib

TARGET = lab8CHMI
TEMPLATE = app


SOURCES += main.cpp\
        calculator.cpp \
        test.cpp \
        outputter.cpp

HEADERS  += calculator.h \
        test.h \
        outputter.h

FORMS    += calculator.ui
INCLUDEPATH += /usr/include/qwt-qt4
LIBS += -L/usr/lib -lqwt-qt4
