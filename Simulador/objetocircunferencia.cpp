#include "objetocircunferencia.h"

ObjetoCircunferencia::ObjetoCircunferencia(float radio_, float masa_, float roce_, float posicionInicialX_, float posicionInicialY_, float posicionInicialZ_)
{
    radio = radio_;
    masa = masa_;
    roce = roce_;
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

    // circulo
    p->drawEllipse(QPointF((qreal)pos[0],(qreal)pos[1]), (qreal)radio, (qreal)radio);

    // lina marca el norte
    dVector3 t1,t2;
    t1[0] = radio*1.2;
    t1[1] = 0;
    t1[2] = 0;
    t1[3] = 0;
    dMULTIPLY0_331 (t2,R,t1);

    p->drawLine(QPointF(pos[0], pos[1]), QPointF(pos[0] + t2[0], pos[1] + t2[1]));
}

void ObjetoCircunferencia::odeLoop() {
    const dReal *v,*w;
    // Roce
    v = dBodyGetLinearVel(body);
    w = dBodyGetAngularVel(body);
    dBodyAddForce (body, -roce*v[0], -roce*v[1], -roce*v[2]);
    dBodyAddTorque (body, -roce*w[0]/4, -roce*w[1]/4, -roce*w[2]/4);

}
