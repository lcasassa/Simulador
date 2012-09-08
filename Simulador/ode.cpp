#include <QtDebug>
#include <ode/ode.h>

#include "ode.h"
#include "simulador.h"
#include "objetocircunferencia.h"
#include "objetolinea.h"
#include "robotquadrotor.h"

// dynamics and collision objects
static dWorldID world;
static dSpaceID space;
static dJointGroupID contactgroup;

Ode::Ode(Simulador *simulador_, QObject *parent) :
    QThread(parent)
{
    simulador = simulador_;
    simulador->registrarObjeto(new ObjetoCircunferencia());
    simulador->registrarObjeto(new RobotQuadrotor());
/*
    simulador->registrarObjeto(new ObjetoLinea(QPointF(-1, -1), QPointF( 1, -1.4)));

    simulador->registrarObjeto(new ObjetoLinea(QPointF(-4, 4), QPointF( 4, 4.5)));
    simulador->registrarObjeto(new ObjetoLinea(QPointF( 4, 4), QPointF( 4,-4.5)));
    simulador->registrarObjeto(new ObjetoLinea(QPointF( 4,-4), QPointF(-4,-4.5)));
    simulador->registrarObjeto(new ObjetoLinea(QPointF(-4,-4), QPointF(-4, 4.5)));
 */
    qreal ancho=0.1, largo=4.5;
    simulador->registrarObjeto(new ObjetoLinea(QPointF(largo, largo), QPointF(-largo, largo+ancho))); // arriba
    simulador->registrarObjeto(new ObjetoLinea(QPointF(largo+ancho,-largo), QPointF( largo, largo))); // derecha
    simulador->registrarObjeto(new ObjetoLinea(QPointF(largo,-largo), QPointF( -largo, -largo-ancho))); // abajo
    simulador->registrarObjeto(new ObjetoLinea(QPointF(-largo,-largo), QPointF( -largo-ancho, largo))); // izquiera
}

static void nearCallback (void *data, dGeomID o1, dGeomID o2);

void Ode::stopOde() {
    running = 0;
}

void Ode::run() {

    running = 1;

    dInitODE ();
    // create world
    world = dWorldCreate ();
    space = dHashSpaceCreate (0);
//    dWorldSetGravity (world,-0.2,-9.8,0);
    dWorldSetCFM (world,1e-5);
    contactgroup = dJointGroupCreate (0);

    //loop objeto fisico
    for (int i = 0; i < simulador->listaObjetoFisico.size(); ++i) {
        simulador->listaObjetoFisico[i]->init(&world, &space);
    }


    // run simulation
//    dsSimulationLoop (0,0,352,288,0);
    while(running) {
        // find collisions and add contact joints
        dSpaceCollide (space,0,&nearCallback);

        for (int i = 0; i < simulador->listaObjetoFisico.size(); ++i) {
            simulador->listaObjetoFisico[i]->odeLoop();
        }

        // step the simulation
        dWorldQuickStep (world,0.01);
        // remove all contact joints
        dJointGroupEmpty (contactgroup);
        // redraw sphere at new location

        for (int i = 0; i < simulador->listaObjetoFisico.size(); ++i) {
            simulador->listaObjetoFisico[i]->mutex.lock();
        }
        for (int i = 0; i < simulador->listaObjetoFisico.size(); ++i) {
            simulador->listaObjetoFisico[i]->mutex.unlock();
        }

//        if(i++%10==0)
//          qWarning() << (float)pos[0] << (float)pos[1] << (float)pos[2];
        //    dsDrawSphere (pos,R,dGeomSphereGetRadius (geom));
        this->msleep(10);

    }

    // clean up
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
//    exec();
}

static void nearCallback (void *data, dGeomID o1, dGeomID o2)
{
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
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
