#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T18:01:15
#
#-------------------------------------------------

QT       += core
QT -= gui

TARGET = plotFuzzy
TEMPLATE = app

#QMAKE_CXXFLAGS += -O2
#QMAKE_LFLAGS += -O2

INCLUDEPATH += ../../fuzzylite-3.0/src/fuzzylite/
#LIBS += -L../../../fuzzylite/ -lfuzzylite
LIBS += -L../../fuzzylite-3.0/src/fuzzylite/lib/ -lfuzzylite-static

SOURCES += \
    plotFuzzy.cpp \
    fuzzyficacion.cpp

HEADERS  += fuzzyficacion.h
