#ifndef ROBOTQUADROTOR_H
#define ROBOTQUADROTOR_H

#include "objetofisico.h"
#include "objetocircunferencia.h"
#include "sensorinfrarrojo.h"

#include "controlfuzzy.h"

class RobotQuadrotor : public ObjetoFisico
{
public:
    RobotQuadrotor(ControlFuzzy *control_ = NULL, float posicionInicialX_ = 0, float posicionInicialY_ = 0);
    ~RobotQuadrotor();
//    void setControl(Control *control_);
    void init(dWorldID *world, dSpaceID *space);
    void remove();
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
    double getMinDistance();
    double getPromDistance();
    double getPromMinDistance();
    double getSumG();
    double getMaxG();
    int crashCount();
    int getObjectDetectedCount();

private:
    dReal vel_old[3];
    int iterations;
    bool objectDetectedOld;
    int objectDetectedCount;
    double minDistance;
    double promDistance;
    double promDistanceTotal;
    double promMinDistanceTotal;
    double prom;
    double sumg;
    double maxg;
    double elapsedTime_old;
    void pintarCirculo(QPainter *p, int i);
    bool isSensorInfrarrojo(dGeomID o1);
    bool isGeom(dGeomID o1);
//    ObjetoCircunferencia *objetoCircunferencia[4];
    SensorInfrarrojo *sensorInfrarrojo[4][4];
    qreal distancia_old[4*4];
//    dJointID    joint[3];
    dBodyID body;
    dGeomID geom[4];
    dMass m;
    float radio;
    float masa;
    float density;
    Control *control;
    bool deleteFizzyficacion;
    float posicionInicialX;
    float posicionInicialY;
    int loopControlCount;
    dReal forceControl[3];
    int crash;
};

#endif // ROBOTQUADROTOR_H
