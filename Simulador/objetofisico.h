#ifndef OBJETOFISICO_H
#define OBJETOFISICO_H

#include <QPainter>
#include <QMutex>
#include <ode/ode.h>

class ObjetoFisico
{
public:
    ObjetoFisico();
    virtual void init(dWorldID *world, dSpaceID *space);
    virtual void odeLoop();
    virtual void pintar(QPainter *p);
    QMutex mutex;
};

#endif // OBJETOFISICO_H
