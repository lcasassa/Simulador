#ifndef ROBOTQUADROTOR_H
#define ROBOTQUADROTOR_H

#include "objetofisico.h"
#include "objetocircunferencia.h"
#include "sensorinfrarrojo.h"

#include "controlfuzzy.h"

class RobotQuadrotor : public ObjetoFisico
{
public:
    RobotQuadrotor();
    ~RobotQuadrotor();
//    void setControl(Control *control_);
    void init(dWorldID *world, dSpaceID *space);
    void pintar(QPainter *p);
    void odeLoop();
    void lock();
    void unlock();
    bool odeCollide(dGeomID o1, dGeomID o2);
    static bool key_up;
    static bool key_down;
    static bool key_left;
    static bool key_right;
    static bool key_clock;
    static bool key_anticlock;

private:
    void pintarCirculo(QPainter *p, int i);
    bool isSensorInfrarrojo(dGeomID o1);
    bool isGeom(dGeomID o1);
//    ObjetoCircunferencia *objetoCircunferencia[4];
    SensorInfrarrojo *sensorInfrarrojo[4][4];
//    dJointID    joint[3];
    dBodyID body;
    dGeomID geom[4];
    dMass m;
    float radio;
    float masa;
//    Control *control;
};

#endif // ROBOTQUADROTOR_H
