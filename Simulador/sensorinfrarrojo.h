#ifndef SENSORINFRARROJO_H
#define SENSORINFRARROJO_H

#include "objetofisico.h"

class SensorInfrarrojo : public ObjetoFisico
{
public:
    SensorInfrarrojo(dReal distanciaMaxDetector_, dReal posX_ = 0.0, dReal posY_ = 0.0, dReal thetaZ_ = 0.0);
    void init(dWorldID *world, dSpaceID *space);
    void remove();
    void pintar(QPainter *p);
    void odeLoop();
    bool odeCollide(dGeomID o1, dGeomID o2);
    void setPose(dReal x, dReal y, dReal z, dReal dx, dReal dy, dReal dz);
    void setPose(dReal x, dReal y, dReal dx, dReal dy);
    void setPose(dReal x, dReal y, dReal theta);
    void lock();
    void unlock();
    dGeomID geom;
    dReal distanciaDetectado;
    double getDistancia();

private:
    dVector3 pos, dir, plus;
    dReal distancia;
    dVector3 bodyDetected;
    dVector3 bodyDetected_;
    dContactGeom contact;
    dReal distanciaMaxDetector;
    dReal posX;
    dReal posY;
    dReal thetaZ;
};

#endif // SENSORINFRARROJO_H
