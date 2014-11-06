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

INCLUDEPATH += ../../fuzzylite/src/fuzzylite/
#LIBS += -L../../../fuzzylite/ -lfuzzylite
LIBS += -L../../fuzzylite/src/fuzzylite/lib/ -lfuzzylite-static

SOURCES += \
    plotFuzzy.cpp \
    fuzzyficacion.cpp

HEADERS  += fuzzyficacion.h

#unix {
#    CONFIG += link_pkgconfig
#    PKGCONFIG += ode
#    PKG_CONFIG_PATH = /Users/linuscasassa/Bibliotecas/install/bin
#}


#LIBS += -lmat
# ode 0.12, 0.11 de ubuntu no!
unix: !mac: {
    #CONFIG += link_pkgconfig
    #PKGCONFIG += ode
    DEFINES += dDOUBLE
    LIBS += -L../ode-0.12/ode/src -lode
    INCLUDEPATH += ../ode-0.12/include

}
unix: mac: {
    #DEFINES += dSINGLE #32 bits
    DEFINES += dDOUBLE #64 bits
    LIBS += -L/usr/local/Cellar/ode/0.12/lib -lode
    INCLUDEPATH += /usr/local/Cellar/ode/0.12/include/
}
