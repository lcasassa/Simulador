#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QWidget>
#include <QList>

#include "ode.h"
#include "trainer.h"
#include "objetofisico.h"
#include "robotquadrotor.h"

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
    Ode *ode;
    Trainer *trainer;

public slots:
    void play(bool sendCommandDone = true);
    void step(int steps_ = 1);
    void pause();
    void reset();
    void stop(bool sendCommandDone = true);
    void registrarObjeto(ObjetoFisico *objetoFisico, bool sendCommandDone = true);
    void desregistrarObjeto(ObjetoFisico *objetoFisico, bool sendCommandDone = true);

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;
    RobotQuadrotor *quad;

private slots:
    void timeout();
    void odeCommandDone();

signals:
    void commandDone();
    
};

#endif // SIMULADOR_H
