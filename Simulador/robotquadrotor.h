#ifndef ROBOTQUADROTOR_H
#define ROBOTQUADROTOR_H

#include "objetofisico.h"
#include "objetocircunferencia.h"

class RobotQuadrotor : public ObjetoFisico
{
public:
    RobotQuadrotor();
    ~RobotQuadrotor();
    void init(dWorldID *world, dSpaceID *space);
    void pintar(QPainter *p);
    void odeLoop();

private:
    ObjetoCircunferencia *objetoCircunferencia[4];
};

#endif // ROBOTQUADROTOR_H
