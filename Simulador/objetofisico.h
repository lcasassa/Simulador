#ifndef OBJETOFISICO_H
#define OBJETOFISICO_H

#include <QPainter>
#include <QMutex>
#include <ode/ode.h>

class ObjetoFisico
{
public:
    ObjetoFisico();
    virtual void pintar(QPainter &p);
    virtual void init(dWorldID *world, dSpaceID *space);
    QMutex mutex;
};

#endif // OBJETOFISICO_H
