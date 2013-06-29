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
public:
    explicit Ode(Simulador *simulador_, QObject *parent = 0);
    void stopOde();
    static void nearCallback(void *data, dGeomID o1, dGeomID o2);
    int sleepTime;
//    void setControl(Control *control);

protected:
    void run();

private:
    RobotQuadrotor *robotQuadrotor;
    Simulador *simulador;
    int running;

signals:
    
public slots:
    
};

#endif // ODE_H
