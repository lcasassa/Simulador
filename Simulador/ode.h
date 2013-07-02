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
    enum RUNNINGMODE { STEP, PAUSE, PLAY };
public:
    explicit Ode(Simulador *simulador_, QObject *parent = 0);
    void stopOde();
    void playOde();
    void pauseOde();
    void stepOde();
    bool isRunning();
    static void nearCallback(void *data, dGeomID o1, dGeomID o2);
    static int sleepTime;

protected:
    void run();
    void lockObjetosFisicos();
    void unlockObjetosFisicos();

private:
    Simulador *simulador;
    int running;
    enum RUNNINGMODE runningMode;

signals:
    
public slots:
    
};

#endif // ODE_H
