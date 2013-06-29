#ifndef OBJETOLINEA_H
#define OBJETOLINEA_H

#include <QPainter>
#include <ode/ode.h>
#include "objetofisico.h"

class ObjetoLinea : public ObjetoFisico
{
public:
    ObjetoLinea(QPointF inicio_, QPointF fin_);
    ~ObjetoLinea();
    void init(dWorldID *world, dSpaceID *space);
    void pintar(QPainter *p);

private:
    QPointF inicio;
    QPointF fin;
    dGeomID geom;

};

#endif // OBJETOLINEA_H
