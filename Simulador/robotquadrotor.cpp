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

#define USER_ACCELERATION_XY 0.1


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
    promMinDistanceTotal = 0;
    sumg = 0;
    maxg = 0;
    iterations = 0;
    crash = 0;
    objectDetectedOld = false;
    objectDetectedCount = 0;
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

    minDistance = radio*5;
    prom = 0;
    promDistanceTotal = 0;
    promMinDistanceTotal = 0;
    sumg = 0;
    iterations = 0;
    maxg = 0;
    crash = 0;
    objectDetectedOld = false;
    objectDetectedCount = 0;

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
        dBodyAddRelForce (body,  USER_ACCELERATION_XY,  0.0, 0);
    if(key_down)
        dBodyAddRelForce (body, -1*USER_ACCELERATION_XY,  0.0, 0);
    if(key_left)
        dBodyAddRelForce (body,  0.0,  USER_ACCELERATION_XY, 0);
    if(key_right)
        dBodyAddRelForce (body,  0.0, -1*USER_ACCELERATION_XY, 0);
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
        dBodyAddRelForce (body, out_[0]/20, out_[1]/20, 0);
        const dReal * rotation = dBodyGetRotation(body);
        forceControl[0] = out_[0]/20*rotation[0] - out_[1]/20*rotation[1];
        forceControl[1] = -out_[0]/20*rotation[4] + out_[1]/20*rotation[5];
        forceControl[2] = 0;

    } else {
        const dReal * rotation = dBodyGetRotation(body);
        dBodyAddRelForce (body, forceControl[0]*rotation[0] + forceControl[1]*rotation[1], forceControl[0]*rotation[4] + forceControl[1]*rotation[5], forceControl[2]);
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
    promDistanceTotal += sum;

    //prom = prom + ( - prom)*0.2;


    //if(distance < 1e-10)
    //    return true;

    bool objectDetected = false;
    double minDistance_tmp = 1;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++) {
            if(minDistance_tmp > (double)distancia_old[i*4+j])
                minDistance_tmp = (double)distancia_old[i*4+j];
            if(minDistance > (double)distancia_old[i*4+j])
                minDistance = (double)distancia_old[i*4+j];
            if(distancia_old[i*4+j] != 1)
                objectDetected = true;
        }

    promMinDistanceTotal += minDistance_tmp;

    if(!objectDetectedOld && objectDetected)
        objectDetectedCount++;

    objectDetectedOld = objectDetected;
    /*
    const dReal *vel;
    vel = dBodyGetLinearVel(body);
    dReal acc[3];

    acc[0] = vel[0] - vel_old[0];
    vel_old[0] = vel[0];
    acc[1] = vel[1] - vel_old[1];
    vel_old[1] = vel[1];*/


    const dReal *a = dBodyGetForce(body);
    double va = sqrt(a[0]*a[0] + a[1]*a[1]);
    //double va = sqrt(acc[0]*acc[0] + acc[1]*acc[1]);
    if(va > maxg)
        maxg = va;
    sumg += va;
    iterations += 1;

}

int RobotQuadrotor::crashCount() {
    return crash;
}

int RobotQuadrotor::getObjectDetectedCount() {
    return objectDetectedCount;
}

double RobotQuadrotor::getSumG() {
    double r = sumg/(iterations*0.01);
    return r;
}

double RobotQuadrotor::getMaxG() {
    double r = maxg/(0.01);
    //qWarning("maxg %f sumg %f", r, sumg/(iterations*USER_ACCELERATION_XY));
    /*
    if(r > 1)
        return 1;
    else if(r<0)
        return 0;
*/
    return r;
}

double RobotQuadrotor::getMinDistance() {
    return minDistance/(1); // radio of the circles
}

double RobotQuadrotor::getPromMinDistance() {
    return promMinDistanceTotal/(iterations*1); // radio of the circles
}

double RobotQuadrotor::getPromDistance() {
    /*
    double prom = 0.0;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            prom += sensorInfrarrojo[i][j]->getProm();

    return prom / (4.0*4.0);
    */

    return promDistanceTotal/(16*iterations*1);

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
    if(isGeom(o1) || isGeom(o2)) {

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
            crash += 1;
        }
    }

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
