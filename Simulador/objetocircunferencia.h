#ifndef OBJETOCIRCUNFERENCIA_H
#define OBJETOCIRCUNFERENCIA_H

#include <QPainter>
#include <ode/ode.h>
#include "objetofisico.h"

class ObjetoCircunferencia : public ObjetoFisico
{
public:
    ObjetoCircunferencia(float radio_ = 0.5, float masa_ = 1.0, int posicionInicialX_ = 0, int posicionInicialY_ = 0, int posicionInicialZ_ = 0);
    void init(dWorldID *world, dSpaceID *space);
    void pintar(QPainter *p);
    dBodyID body;

private:
    dGeomID geom;
    dMass m;
    float radio;
    float masa;
    int posicionInicialX;
    int posicionInicialY;
    int posicionInicialZ;
};

#endif // OBJETOCIRCUNFERENCIA_H
