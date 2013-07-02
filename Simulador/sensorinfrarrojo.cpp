#include "sensorinfrarrojo.h"
#include <ode/ode.h>

SensorInfrarrojo::SensorInfrarrojo(dReal distanciaMaxDetector_, dReal posX_, dReal posY_, dReal thetaZ_)
{
    distanciaMaxDetector = distanciaMaxDetector_;
    posX = posX_;
    posY = posY_;
    thetaZ = thetaZ_;
}

void SensorInfrarrojo::init(dWorldID *world, dSpaceID *space) {
    geom = dCreateRay(*space, distanciaMaxDetector);
    setPose(posX, posY, thetaZ);
//    geom; dGeomDisable(
//    dGeomSetRotation(geom,R);
}

void SensorInfrarrojo::setPose(dReal x, dReal y, dReal z, dReal dx, dReal dy, dReal dz) {
//    qWarning("SensorInfrarrojo::setPose(%f, %f,%f, %f, %f, %f)", x, y, z, dx, dy, dz);
    dGeomRaySet (geom, x,y,z, dx,dy,dz);
}

void SensorInfrarrojo::setPose(dReal x, dReal y, dReal dx, dReal dy) {
//    qWarning("SensorInfrarrojo::setPose(%f, %f, %f, %f)", x, y, dx, dy);
    setPose (x,y,0, dx,dy,0);
}

void SensorInfrarrojo::setPose(dReal x, dReal y, dReal theta) {
//    qWarning("SensorInfrarrojo::setPose(%f, %f, %f)", x, y, theta);
    setPose (x,y,0, cos(theta),sin(theta),0);
}

void SensorInfrarrojo::odeLoop() {
//    qWarning("d: %f", distancia);

    if(bodyDetected_[0] != 0 || bodyDetected_[1] != 0 || bodyDetected_[2] != 0) {
        bodyDetected[0] = bodyDetected_[0];
        bodyDetected[1] = bodyDetected_[1];
        bodyDetected[2] = bodyDetected_[2];
    } else {
        dGeomRayGet(geom, pos, dir);
        dNormalize3(dir);
        dScaleVector3(dir,distanciaMaxDetector);
        dAddVectors3(plus, dir, pos);
        bodyDetected[0] = plus[0];
        bodyDetected[1] = plus[1];
        bodyDetected[2] = plus[2];
    }

    bodyDetected_[0] = 0;
    bodyDetected_[1] = 0;
    bodyDetected_[2] = 0;
    distanciaDetectado = distancia;
    distancia = distanciaMaxDetector;

}

void SensorInfrarrojo::pintar(QPainter *p) {
    mutex.lock();

    QPen backup_pen = p->pen();
    QPen pen;
    pen.setWidthF(0.01);

    pen.setColor(Qt::red);
    p->setPen(pen);

//    if(distancia > 3)
//        p->drawLine(QPointF(pos[0], pos[1]), QPointF(bodyDetected[0]*1.1, bodyDetected[1]*1.1));
//    else

    dVector3 pos, dir;
    dGeomRayGet(geom, pos, dir);
    p->drawLine(QPointF(pos[0], pos[1]), QPointF(bodyDetected[0], bodyDetected[1]));


    p->setPen(backup_pen);
    mutex.unlock();
}

bool SensorInfrarrojo::odeCollide(dGeomID o1, dGeomID o2) {
    if(o2 == geom) {
        o2 = o1;
        o1 = geom;
    }
    if(o1 == geom) {
        const dReal *p1;
        dReal *p2;
        dReal p3;
        int numc;
        if (numc = dCollide (o1, o2, 1, &contact, sizeof(dContactGeom))) {
            p2 = (dReal*)&contact.pos;
        } else {
            return true;
        }

        p1 = dGeomGetPosition(o1);
//        bodyDetected = dGeomGetPosition(o2);

        p3 = dDISTANCE(p1, p2);
        if(p3 < distancia) {
            distancia = p3;
            bodyDetected_[0] = p2[0];
            bodyDetected_[1] = p2[1];
            bodyDetected_[2] = p2[2];
        }

        return true;
    }
    return false;
}

void SensorInfrarrojo::lock() {
    mutex.lock();
}

void SensorInfrarrojo::unlock() {
    mutex.unlock();
}
