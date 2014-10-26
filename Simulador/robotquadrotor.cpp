#include "robotquadrotor.h"
#include "ode.h"
//#include <ode/ode.h>
#include <QStringList>
#include <QCoreApplication>

bool RobotQuadrotor::key_up = false;
bool RobotQuadrotor::key_down = false;
bool RobotQuadrotor::key_left = false;
bool RobotQuadrotor::key_right = false;
bool RobotQuadrotor::key_clock = false;
bool RobotQuadrotor::key_anticlock = false;


RobotQuadrotor::RobotQuadrotor(ControlFuzzy *control_, float posicionInicialX_, float posicionInicialY_)
{
    loopControlCount=0;
    posicionInicialX = posicionInicialX_;
    posicionInicialY = posicionInicialY_;

    radio = 0.3;
    masa = 1;

    QStringList argumentList(QCoreApplication::arguments());
    if(argumentList.size() == 5)
        density = argumentList[4].toFloat();
    if(argumentList.size() == 3)
        density = argumentList[2].toFloat();
    else
        density = 1;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            sensorInfrarrojo[i][j] = new SensorInfrarrojo(radio*5);

    minDistance = radio*5;
    promDistance = -1;

    for(int i=0; i<4*4; i++)
        distancia_old[i]=radio*5;

    control = control_;

    prom = 0;
    promDistanceTotal = 0;
    sumg = 0;
}

RobotQuadrotor::~RobotQuadrotor() {

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            delete sensorInfrarrojo[i][j];

}

void RobotQuadrotor::init(dWorldID *world, dSpaceID *space) {

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        sensorInfrarrojo[i][j]->init(world, space);

    body = dBodyCreate(*world);
    geom[0] = dCreateSphere(*space, radio);
    geom[1] = dCreateSphere(*space, radio);
    geom[2] = dCreateSphere(*space, radio);
    geom[3] = dCreateSphere(*space, radio);
    dMassSetSphere(&m, density, masa);
    dBodySetMass(body, &m);
    dGeomSetBody(geom[0], body);
    dGeomSetBody(geom[1], body);
    dGeomSetBody(geom[2], body);
    dGeomSetBody(geom[3], body);
    // set initial position
    dBodySetPosition(body, posicionInicialX, posicionInicialY, 0);

    dGeomSetOffsetPosition( geom[0],  radio,  radio, 0);
    dGeomSetOffsetPosition( geom[1],  radio, -radio, 0);
    dGeomSetOffsetPosition( geom[2], -radio,  radio, 0);
    dGeomSetOffsetPosition( geom[3], -radio, -radio, 0);

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            dGeomSetBody( sensorInfrarrojo[i][j]->geom, body );

    // position and rotation setting
    for(int j=0; j<4; j++) {
        dGeomSetOffsetPosition( sensorInfrarrojo[0][j]->geom,  radio,  radio, 0.0 );
        dGeomSetOffsetPosition( sensorInfrarrojo[1][j]->geom, -radio,  radio, 0.0 );
        dGeomSetOffsetPosition( sensorInfrarrojo[2][j]->geom, -radio, -radio, 0.0 );
        dGeomSetOffsetPosition( sensorInfrarrojo[3][j]->geom,  radio, -radio, 0.0 );
    }

    dMatrix3 R;
    for(int j=0; j<4; j++) {
        dRFromAxisAndAngle( R, sin(-(j*30)*M_PI/180), cos(-(j*30)*M_PI/180), 0.0, 90.0*M_PI/180 );
        dGeomSetOffsetRotation( sensorInfrarrojo[0][j]->geom, R );

        dRFromAxisAndAngle( R, sin(-(j*30+90)*M_PI/180), cos(-(j*30+90)*M_PI/180), 0.0, 90.0*M_PI/180 );
        dGeomSetOffsetRotation( sensorInfrarrojo[1][j]->geom, R );

        dRFromAxisAndAngle( R, sin(-(j*30+180)*M_PI/180), cos(-(j*30+180)*M_PI/180), 0.0, 90.0*M_PI/180 );
        dGeomSetOffsetRotation( sensorInfrarrojo[2][j]->geom, R );

        dRFromAxisAndAngle( R, sin(-(j*30+270)*M_PI/180), cos(-(j*30+270)*M_PI/180), 0.0, 90.0*M_PI/180 );
        dGeomSetOffsetRotation( sensorInfrarrojo[3][j]->geom, R );
    }

    prom = 0;
    promDistanceTotal = 0;
    sumg = 0;

    ObjetoFisico::init(world, space);
}

void RobotQuadrotor::remove() {

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            sensorInfrarrojo[i][j]->remove();

    for(int j=0; j<4; j++)
        dGeomDestroy(geom[j]);

    dBodyDestroy(body);
}

void RobotQuadrotor::odeLoop() {
    //static int j=0;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            sensorInfrarrojo[i][j]->odeLoop();

    //dBodyAddRelForce (body,  0.001, 0, 0);

    if(key_up)
        dBodyAddRelForce (body,  0.3,  0.0, 0);
    if(key_down)
        dBodyAddRelForce (body, -0.3,  0.0, 0);
    if(key_left)
        dBodyAddRelForce (body,  0.0,  0.3, 0);
    if(key_right)
        dBodyAddRelForce (body,  0.0, -0.3, 0);
    if(key_clock)
        dBodyAddTorque (body,  0.0, 0.0, -0.1);
    if(key_anticlock)
        dBodyAddTorque (body,  0.0, 0.0,  0.1);


    if(control != NULL && (loopControlCount++%20)==0) {
        qreal distancia_[4*4];
        qreal vel_[4*4];
        qreal out_[2];

        // 0 a 1
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++) {
                distancia_[i*4+j] = ( sensorInfrarrojo[i][j]->distanciaDetectado - 0.3 ) / (0.3*5 - 0.3);
                vel_[i*4+j] = distancia_[i*4+j] - distancia_old[i*4+j];
                distancia_old[i*4+j] = distancia_[i*4+j];
            }

        control->loopControl(distancia_, vel_, out_);
        dBodyAddRelForce (body, out_[0], out_[1], 0);
    }

    // Roce
//    dBodyAddRelForce (body, cos((j++%3141)/1000)*0.3, 0, 0);
//    dBodyAddTorque (body, 0, 0, cos(j%3141/1000)*0.001);
//    qWarning("det: %f -> %f", sensorInfrarrojo[0][0]->distanciaDetectado, (1.5-sensorInfrarrojo[0][0]->distanciaDetectado)*1);
//    if((1.5-sensorInfrarrojo[0][0]->distanciaDetectado) != 0)
//        dBodyAddForceAtRelPos (body, -(1.5-sensorInfrarrojo[0][0]->distanciaDetectado)*1, 0.2, 0, -radio, radio, 0);

    const dReal *v,*w;
    dReal roce=0.01;
    // Roce
    v = dBodyGetLinearVel(body);
    w = dBodyGetAngularVel(body);
    dBodyAddForce (body, -roce*v[0], -roce*v[1], -roce*v[2]);
    dBodyAddTorque (body, -roce*w[0]*2, -roce*w[1]*2, -roce*w[2]*2);


    double sum=0;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            sum += (double)distancia_old[i*4+j];
    promDistanceTotal = promDistanceTotal + (sum - promDistanceTotal)*0.2;

    const dReal *a;
    a = dBodyGetForce(body);

    sumg += a[0] + a[1];

    //prom = prom + ( - prom)*0.2;


    //if(distance < 1e-10)
    //    return true;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(minDistance > (double)distancia_old[i*4+j])
                minDistance = (double)distancia_old[i*4+j];

}

double RobotQuadrotor::getSumG() {
    return sumg;
}

double RobotQuadrotor::getMinDistance() {
    return minDistance; // radio of the circles
}

double RobotQuadrotor::getPromDistance() {
    /*
    double prom = 0.0;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            prom += sensorInfrarrojo[i][j]->getProm();

    return prom / (4.0*4.0);
    */

    return promDistanceTotal;

    //return promDistance - 0.3; // radio of the circles
}


void RobotQuadrotor::pintarCirculo(QPainter *p, int i) {
    const dReal *pos;
//    const dReal *R;

    mutex.lock();
    pos = dGeomGetPosition (geom[i]);
//    R = dGeomGetRotation (geom[i]);
    mutex.unlock();

    // circulo
    p->drawEllipse(QPointF((qreal)pos[0],(qreal)pos[1]), (qreal)radio, (qreal)radio);
}

void RobotQuadrotor::pintar(QPainter *p) {
/*    for(int i=0; i<4; i++) {
        objetoCircunferencia[i]->pintar(p);
    }*/

    pintarCirculo(p,0);
    pintarCirculo(p,1);
    pintarCirculo(p,2);
    pintarCirculo(p,3);

    dVector3 t1,t2;
    const dReal *pos;
    const dReal *R;

    mutex.lock();
    pos = dBodyGetPosition(body);
    R = dBodyGetRotation(body);
    mutex.unlock();

    t1[0] = radio*2;
    t1[1] = 0;
    t1[2] = 0;
    t1[3] = 0;
    dMULTIPLY0_331 (t2,R,t1);

    QPen backup_pen = p->pen();
    QPen pen;
    pen.setWidthF(0.02);
    pen.setColor(Qt::green);
    p->setPen(pen);

    p->drawLine(QPointF(pos[0], pos[1]), QPointF(pos[0] + t2[0], pos[1] + t2[1]));

    p->setPen(backup_pen);

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            sensorInfrarrojo[i][j]->pintar(p);

}

void RobotQuadrotor::lock() {
    ObjetoFisico::lock();
/*    for(int i=0; i<4; i++) {
        objetoCircunferencia[i]->lock();
    }*/
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            sensorInfrarrojo[i][j]->lock();
}

void RobotQuadrotor::unlock() {
    ObjetoFisico::unlock();
/*    for(int i=0; i<4; i++) {
        objetoCircunferencia[i]->unlock();
    }*/
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            sensorInfrarrojo[i][j]->unlock();
}

bool RobotQuadrotor::isSensorInfrarrojo(dGeomID o1) {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(sensorInfrarrojo[i][j]->geom == o1) return true;
    return false;
}

bool RobotQuadrotor::isGeom(dGeomID o1) {
    for(int i=0; i<4; i++) {
        if(geom[i] == o1) return true;
    }
    return false;
}

bool RobotQuadrotor::odeCollide(dGeomID o1, dGeomID o2) {
/*    for(int i=0; i<4; i++) {
        if(objetoCircunferencia[i]->odeCollide(o1, o2)) return true;
    }*/

/*    if((isGeom(o1) && isSensorInfrarrojo(o2)) || (isGeom(o2) && isSensorInfrarrojo(o1))) {
            return true;
    }*/

    for(int i=0; i<4; i++)
        for(int j=0; j<4 ; j++)
            if(sensorInfrarrojo[i][j]->odeCollide(o1, o2))
                return true;

    return false;
}
