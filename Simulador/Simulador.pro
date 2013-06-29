#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T18:01:15
#
#-------------------------------------------------

QT       += core gui

TARGET = Simulador
TEMPLATE = app

INCLUDEPATH += ../fuzzylite
LIBS += -L../fuzzylite/unix-static -lfuzzylite

SOURCES += main.cpp\
    mainwindow.cpp \
    simulador.cpp \
    objetofisico.cpp \
    ode.cpp \
    objetocircunferencia.cpp \
    objetolinea.cpp \
    robotquadrotor.cpp \
    sensorinfrarrojo.cpp \
    controlfuzzy.cpp \
    control.cpp \
    areatriangular.cpp \
    fuzzyficacion.cpp

HEADERS  += mainwindow.h \
    simulador.h \
    objetofisico.h \
    ode.h \
    objetocircunferencia.h \
    objetolinea.h \
    robotquadrotor.h \
    sensorinfrarrojo.h \
    controlfuzzy.h \
    control.h \
    areatriangular.h \
    fuzzyficacion.h

FORMS    += mainwindow.ui

#unix {
#    CONFIG += link_pkgconfig
#    PKGCONFIG += ode
#    PKG_CONFIG_PATH = /Users/linuscasassa/Bibliotecas/install/bin
#}

unix: !mac: {
    DEFINES += dSINGLE
    LIBS += -L/usr/lib -lode
    INCLUDEPATH += /usr/include/
}
unix: mac: {
    DEFINES += dSINGLE
    LIBS += -L/usr/local/Cellar/ode/0.12/lib -lode
    INCLUDEPATH += /usr/local/Cellar/ode/0.12/include/
}
