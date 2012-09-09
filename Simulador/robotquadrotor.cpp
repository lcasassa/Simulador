#include "robotquadrotor.h"
#include <ode/ode.h>

RobotQuadrotor::RobotQuadrotor()
{
    int i=0;
    objetoCircunferencia[i++] = new ObjetoCircunferencia(0.5,0.3,1,  0.5, 0.5);
    objetoCircunferencia[i++] = new ObjetoCircunferencia(0.5,0.3,1, -0.5, 0.5);
    objetoCircunferencia[i++] = new ObjetoCircunferencia(0.5,0.3,1,  0.5,-0.5);
    objetoCircunferencia[i++] = new ObjetoCircunferencia(0.5,0.3,1, -0.5,-0.5);

}

void RobotQuadrotor::init(dWorldID *world, dSpaceID *space) {
    for(int i=0; i<4; i++) {
        objetoCircunferencia[i]->init(world, space);
    }
}

void RobotQuadrotor::odeLoop() {
    for(int i=0; i<4; i++) {
        objetoCircunferencia[i]->odeLoop();
    }
    // Roce
    dBodyAddRelForce (objetoCircunferencia[0]->body, 1, 0.5, 0);
    dBodyAddTorque (objetoCircunferencia[0]->body, 0, 0, 0.2);
}

void RobotQuadrotor::pintar(QPainter *p) {
    for(int i=0; i<4; i++) {
        objetoCircunferencia[i]->pintar(p);
    }
}
