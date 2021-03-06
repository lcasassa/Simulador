#ifndef OBJETOCIRCUNFERENCIA_H
#define OBJETOCIRCUNFERENCIA_H

#include <QPainter>
#include <ode/ode.h>
#include "objetofisico.h"

class ObjetoCircunferencia : public ObjetoFisico
{
public:
    ObjetoCircunferencia(float radio_ = 0.5, float masa_ = 1.0, float roce_ = 0.1, float posicionInicialX_ = 0.0, float posicionInicialY_ = 0.0, float posicionInicialZ_ = 0.0, float(*xForce_)(float) = NULL, float(*yForce_)(float) = NULL);
    ~ObjetoCircunferencia();
    void init(dWorldID *world, dSpaceID *space);
    void remove();
    void pintar(QPainter *p);
    void odeLoop();
    dBodyID body;

private:
    dGeomID geom;
    dMass m;
    float radio;
    float masa;
    float roce;
    float posicionInicialX;
    float posicionInicialY;
    float posicionInicialZ;
    float tiempo;
    float(*xForce)(float);
    float(*yForce)(float);
};

#endif // OBJETOCIRCUNFERENCIA_H
