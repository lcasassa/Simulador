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
    dBodySetPosition (body,posicionInicialX, posicionInicialY, 0);
    //posicionInicialZ
    //dBodySetRotation(body, );
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

    QPen backup_pen = p->pen();
    QPen pen;
    pen.setWidthF(0.02);
    pen.setColor(Qt::black);
    p->setPen(pen);

    // lina marca el norte
    dVector3 t1,t2;
    t1[0] = radio*1.2;
    t1[1] = 0;
    t1[2] = 0;
    t1[3] = 0;
    dMULTIPLY0_331 (t2,R,t1);

    p->drawLine(QPointF(pos[0], pos[1]), QPointF(pos[0] + t2[0], pos[1] + t2[1]));

    p->setPen(backup_pen);
}

void ObjetoCircunferencia::odeLoop() {
    const dReal *v,*w;
    static int i=0;

    dBodyAddForce (body, sin((float)(i++%(2*3141))/1000.0)*0.3, cos((float)(i++%(2*3141))/1000.0)*0.1, 0);
    // Roce
    v = dBodyGetLinearVel(body);
    w = dBodyGetAngularVel(body);
    dBodyAddForce (body, -roce*v[0], -roce*v[1], -roce*v[2]);
    dBodyAddTorque (body, -roce*w[0]/4, -roce*w[1]/4, -roce*w[2]/4);

}
