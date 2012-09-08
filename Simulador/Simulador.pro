#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T18:01:15
#
#-------------------------------------------------

QT       += core gui

TARGET = Simulador
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    simulador.cpp \
    objetofisico.cpp \
    ode.cpp \
    objetocircunferencia.cpp \
    objetolinea.cpp \
    robotquadrotor.cpp

HEADERS  += mainwindow.h \
    simulador.h \
    objetofisico.h \
    ode.h \
    objetocircunferencia.h \
    objetolinea.h \
    robotquadrotor.h

FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += ode
    PKG_CONFIG_PATH = /Users/linuscasassa/Bibliotecas/install/bin
}
