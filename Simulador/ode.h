#ifndef ODE_H
#define ODE_H

#include <QThread>
#include <ode/ode.h>
#include "control.h"
#include "robotquadrotor.h"

// simulador.h llama a ode.h y por lo tanto ode.h no puede llamar a simulador.h
//#include "simulador.h"
class Simulador;

class Ode : public QThread
{
    Q_OBJECT
    enum STATUS_MODE { ODE_NOT_INIT = -4, SUBSTRACT_ONE = -3, STOP = -2, PLAY = -1, PAUSE = 0, STEP = 1 };
public:
    explicit Ode(Simulador *simulador_, QObject *parent = 0);
    void stopOde();
    void playOde();
    void pauseOde();
    void stepOde(int steps_ = 1);
    bool isRunning();
    void setStatus(int status_);
    int getStatus();
    static void nearCallback(void *data, dGeomID o1, dGeomID o2);
    static int sleepTime;

protected:
    void run();
    void lockObjetosFisicos();
    void unlockObjetosFisicos();

private:
    Simulador *simulador;
    int status;
    QMutex statusMutex;

signals:
    
public slots:
    
};

#endif // ODE_H
