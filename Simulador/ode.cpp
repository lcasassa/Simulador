#include <QtDebug>
//#include <ode/ode.h>

#include <ode/ode.h>
#include "ode.h"
#include "simulador.h"
#include "objetocircunferencia.h"
#include "objetolinea.h"
#include "sensorinfrarrojo.h"

// dynamics and collision objects
static dWorldID world;
static dSpaceID space;
static dJointGroupID contactgroup;

Simulador *sim; //Ode::nearCallback() usa sim y es unfion statica

int Ode::sleepTime = 1000;
double elapsedTime;

Ode::Ode(Simulador *simulador_, QObject *parent) :
    QThread(parent)
{
    setStatus(ODE_NOT_INIT);

    simulador = simulador_;
    sim = simulador;

/*
    simulador->registrarObjeto(new ObjetoLinea(QPointF(-1, -1), QPointF( 1, -1.4)));

    simulador->registrarObjeto(new ObjetoLinea(QPointF(-4, 4), QPointF( 4, 4.5)));
    simulador->registrarObjeto(new ObjetoLinea(QPointF( 4, 4), QPointF( 4,-4.5)));
    simulador->registrarObjeto(new ObjetoLinea(QPointF( 4,-4), QPointF(-4,-4.5)));
    simulador->registrarObjeto(new ObjetoLinea(QPointF(-4,-4), QPointF(-4, 4.5)));
 */

    qreal ancho=0.1, largo=4.5;
    listaObjetosFisicos.append(new ObjetoLinea(QPointF(largo, largo), QPointF(-largo, largo+ancho))); // arriba
    listaObjetosFisicos.append(new ObjetoLinea(QPointF(largo+ancho,-largo), QPointF( largo, largo))); // derecha
    listaObjetosFisicos.append(new ObjetoLinea(QPointF(largo,-largo), QPointF( -largo, -largo-ancho))); // abajo
    listaObjetosFisicos.append(new ObjetoLinea(QPointF(-largo,-largo), QPointF( -largo-ancho, largo))); // izquiera

    foreach(ObjetoFisico *of, listaObjetosFisicos) {
        simulador->registrarObjeto(of);
    }

    //    simulador->registrarObjeto(new SensorInfrarrojo());

    start();
}

/*void Ode::setControl(Control *control) {
    robotQuadrotor->setControl(control);
}*/

Ode::~Ode() {
    foreach(ObjetoFisico *of, listaObjetosFisicos) {
        simulador->desregistrarObjeto(of);
    }
}

void Ode::stopOde() {
    setStatus(STOP);
    while(getStatus() != ODE_NOT_INIT)
        msleep(10);
}

void Ode::playOde(double sec) {
    if(sec < 0.01) sec = 0.01;
    int steps = sec/0.01;
    setStatus(steps);
}

void Ode::pauseOde() {
    setStatus(PAUSE);
}

void Ode::stepOde(int steps_) {
    if(steps_ > 0)
        setStatus(steps_);
    while(getStatus() != PAUSE) msleep(10);
}

bool Ode::isRunning() {
    return (getStatus() >= -1);
}

bool Ode::isPaused() {
    return (getStatus() == PAUSE);
}

int Ode::getStatus() {
    statusMutex.lock();
    int status_ = status;
    statusMutex.unlock();
    return status_;
}

void Ode::setStatus(int status_) {
    statusMutex.lock();
    if(status_ == SUBSTRACT_ONE)
        status -= 1;
    else
        status = status_;
    statusMutex.unlock();
}

void Ode::run() {

    dInitODE ();
    // create world
    world = dWorldCreate ();
    space = dHashSpaceCreate (0);
//    dWorldSetGravity (world,-0.2,-9.8,0);
    dWorldSetCFM (world,1e-5);
    contactgroup = dJointGroupCreate (0);

    elapsedTime = 0;

    setStatus(2); // Para que se pinte bien sensorinfrarrojo.cpp
    // run simulation
//    dsSimulationLoop (0,0,352,288,0);
    while(getStatus() > STOP) {

        //qWarning("iteracion: %f", elapsedTime);
        while(getStatus() == PAUSE)
            this->msleep(50);

        if(getStatus() >= STEP) {
            setStatus(SUBSTRACT_ONE);
        }

        lockObjetosFisicos();
        for (int i = 0; i < simulador->listaObjetoFisico.size(); ++i) {
            if(!simulador->listaObjetoFisico[i]->isOdeInit)
                simulador->listaObjetoFisico[i]->init(&world, &space);
        }

        // find collisions and add contact joints
        dSpaceCollide (space,0,&nearCallback);

        for (int i = 0; i < simulador->listaObjetoFisico.size(); ++i) {
            if(simulador->listaObjetoFisico[i]->isOdeInit)
                simulador->listaObjetoFisico[i]->odeLoop();
        }

        // step the simulation
        dWorldQuickStep (world,0.01);
        elapsedTime += 0.01;
        // remove all contact joints
        dJointGroupEmpty (contactgroup);
        // redraw sphere at new location

        unlockObjetosFisicos();

        int la = sleepTime;
        if(sleepTime != 0)
            this->usleep(la);

        //qWarning("ode loop");
    }

    //odeFinishMutex.lock();
    setStatus(ODE_NOT_INIT);
    while(getStatus() == ODE_NOT_INIT) msleep(10);
    //odeFinishWaitCondition.wait(&odeFinishMutex);
    //odeFinishMutex.unlock();

    // clean up
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
//    exec();
}

/*double Ode::getElapsedTime() {
    return time;
}*/

void Ode::finish() {
    //odeFinishWaitCondition.wakeAll();
    setStatus(STOP);
}

void Ode::lockObjetosFisicos() {
    simulador->listaObjetoFisicoMutex.lock();
    for (int i = 0; i < simulador->listaObjetoFisico.size(); ++i) {
        simulador->listaObjetoFisico[i]->lock();
    }
}

void Ode::unlockObjetosFisicos() {
    for (int i = 0; i < simulador->listaObjetoFisico.size(); ++i) {
        simulador->listaObjetoFisico[i]->unlock();
    }
    simulador->listaObjetoFisicoMutex.unlock();
}

void Ode::nearCallback (void *data, dGeomID o1, dGeomID o2)
{
    for (int i = 0; i < sim->listaObjetoFisico.size(); ++i) {
        if(sim->listaObjetoFisico[i]->odeCollide(o1, o2))
            return;
    }

    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);

//    if(b1 == 0 || b2 == 0) return;

    dContact contact;
    contact.surface.mode = dContactBounce | dContactSoftCFM;
    // friction parameter
    contact.surface.mu = dInfinity;
    // bounce is the amount of "bouncyness".
    contact.surface.bounce = 0.9;
    // bounce_vel is the minimum incoming velocity to cause a bounce
    contact.surface.bounce_vel = 0.1;
    // constraint force mixing parameter
    contact.surface.soft_cfm = 0.001;
    if (int numc = dCollide (o1,o2,1,&contact.geom,sizeof(dContact))) {
        dJointID c = dJointCreateContact (world,contactgroup,&contact);
        dJointAttach (c,b1,b2);
    }

}
