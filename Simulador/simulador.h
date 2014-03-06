#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QWidget>
#include <QList>

#include "ode.h"
#include "trainer.h"
#include "objetofisico.h"
#include "robotquadrotor.h"
#include "plotfuzzy.h"


#define DO_NOT_SEND_SIGNAL_WHEN_DONE false

class Simulador : public QWidget
{
    Q_OBJECT
public:
    Simulador(QWidget *parent = 0);
    ~Simulador();

    bool playPause();
    void setRefrescoHz(int refrescoHz);

    QList<ObjetoFisico*> listaObjetoFisico;
    QMutex listaObjetoFisicoMutex;
    Ode *ode;
    Trainer *trainer;

    void setFuzzyWidgets(PlotFuzzy *widgetInput, PlotFuzzy *widgetOutput);

public slots:
    void play(double sec, bool sendCommandDone = true);
    void step(int steps_ = 1);
    void pause();
    void reset();
    void stop(bool sendCommandDone = true);
    void registrarObjeto(ObjetoFisico *objetoFisico, bool sendCommandDone = true);
    void desregistrarObjeto(ObjetoFisico *objetoFisico, bool sendCommandDone = true);
    void newFuzzy(fuzzy f);
    void odeCommandDone();

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;
    RobotQuadrotor *quad;
    PlotFuzzy *plotFuzzyInput;
    PlotFuzzy *plotFuzzyOutput;

private slots:
    void timeout();

signals:
    void commandDone();
    
};

#endif // SIMULADOR_H
