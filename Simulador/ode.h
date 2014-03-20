#ifndef ODE_H
#define ODE_H

#include <QThread>
#include <ode/ode.h>
#include "control.h"
#include "robotquadrotor.h"
#include <QWaitCondition>

extern double elapsedTime;

// simulador.h llama a ode.h y por lo tanto ode.h no puede llamar a simulador.h
//#include "simulador.h"
class Simulador;

class Ode : public QThread
{
    Q_OBJECT
public:
    enum STATUS_MODE { ODE_NOT_INIT = -4, SUBSTRACT_ONE = -3, STOP = -2, PLAY = -1, PAUSE = 0, STEP = 1 };
    explicit Ode(Simulador *simulador_, QObject *parent = 0);
    ~Ode();
    bool isRunning();
    bool isPaused();
    void setStatus(int status_);
    int getStatus();
    static void nearCallback(void *data, dGeomID o1, dGeomID o2);
    static int sleepTime;
    double getElapsedTime();
    QMutex odeFinishMutex;

public slots:
    void stopOde();
    void playOde(double sec);
    void pauseOde();
    void stepOde(int steps_ = 1);
    void finish();

protected:
    void run();
    void lockObjetosFisicos();
    void unlockObjetosFisicos();

private:
    Simulador *simulador;
    int status;
    QMutex statusMutex;

    QWaitCondition odeFinishWaitCondition;

    QList<ObjetoFisico*> listaObjetosFisicos;

signals:
    void results(int value);

public slots:

    
};

#endif // ODE_H
