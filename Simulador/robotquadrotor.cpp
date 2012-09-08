#include "robotquadrotor.h"
#include <ode/ode.h>

RobotQuadrotor::RobotQuadrotor()
{
    for(int i=0; i<4; i++) {
        objetoCircunferencia[i] = new ObjetoCircunferencia();
    }
}

void RobotQuadrotor::init(dWorldID *world, dSpaceID *space) {
    for(int i=0; i<4; i++) {
        objetoCircunferencia[i]->init(world, space);
    }
}

void RobotQuadrotor::odeLoop() {
    dBodyAddRelForce (objetoCircunferencia[0]->body, 1, 1, 0);
}

void RobotQuadrotor::pintar(QPainter *p) {
    for(int i=0; i<4; i++) {
        objetoCircunferencia[i]->pintar(p);
    }
}
