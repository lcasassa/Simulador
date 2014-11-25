#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T18:01:15
#
#-------------------------------------------------

QT       += core gui

TARGET = Simulador
TEMPLATE = app

#QMAKE_CXXFLAGS += -O2
#QMAKE_LFLAGS += -O2

INCLUDEPATH += ../../fuzzylite-3.0/src/fuzzylite/
#LIBS += -L../../fuzzylite/ -lfuzzylite
LIBS += -L../../fuzzylite-3.0/src/fuzzylite/lib/ -lfuzzylite-static

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
    fuzzyficacion.cpp \
    trainer.cpp \
    traineralgoritmogenetico.cpp \
    plotfuzzy.cpp \
    simgalib/simgalib.cpp \
    simgalib/simpsolib.cpp \
    simgalib/simtstlib.cpp \
    escenariotresobjetos.cpp \
    escenariotresobjetoscerca.cpp \
    escenario.cpp \
    escenariounobjeto.cpp \
    trainertestcontroller.cpp \
    escenariotest.cpp

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
    fuzzyficacion.h \
    trainer.h \
    traineralgoritmogenetico.h \
    plotfuzzy.h \
    simgalib/simgalib.h \
    simgalib/simpsolib.h \
    simgalib/simtstlib.h \
    escenariotresobjetos.h \
    escenariotresobjetoscerca.h \
    escenario.h \
    escenariounobjeto.h \
    trainertestcontroller.h \
    escenariotest.h

FORMS    += mainwindow.ui

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
    LIBS += -L../../ode-0.12/ode/src -lode
    INCLUDEPATH += ../../ode-0.12/include

}
unix: mac: {
    #DEFINES += dSINGLE #32 bits
    DEFINES += dDOUBLE #64 bits
    LIBS += -L/usr/local/Cellar/ode/0.12/lib -lode
    INCLUDEPATH += /usr/local/Cellar/ode/0.12/include/
}
