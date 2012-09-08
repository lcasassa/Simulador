#include "objetocircunferencia.h"

ObjetoCircunferencia::ObjetoCircunferencia(float radio_, float masa_, int posicionInicialX_, int posicionInicialY_, int posicionInicialZ_)
{
    radio = radio_;
    masa = masa_;
    posicionInicialX = posicionInicialX_;
    posicionInicialY = posicionInicialY_;
    posicionInicialZ = posicionInicialZ_;
}

void ObjetoCircunferencia::init(dWorldID *world, dSpaceID *space) {
    // create object
    body = dBodyCreate (*world);
    geom = dCreateSphere (*space,radio);
    dMassSetSphere (&m,1,masa);
    dBodySetMass (body,&m);
    dGeomSetBody (geom,body);
    // set initial position
    dBodySetPosition (body,posicionInicialX, posicionInicialY, posicionInicialZ);
}


void ObjetoCircunferencia::pintar(QPainter *p) {
    const dReal *pos;
    const dReal *R;

    mutex.lock();
    pos = dGeomGetPosition (geom);
    R = dGeomGetRotation (geom);
    mutex.unlock();

    p->drawEllipse(QPointF((qreal)pos[0],(qreal)pos[1]), (qreal)radio, (qreal)radio);
//    p->drawEllipse(0,0,5,5);
//    qWarning("pos: %d", pos[2]);
}
