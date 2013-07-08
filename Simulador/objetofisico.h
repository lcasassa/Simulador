#ifndef OBJETOFISICO_H
#define OBJETOFISICO_H

#include <QPainter>
#include <QMutex>
#include <ode/ode.h>

class ObjetoFisico : public QObject
{
    Q_OBJECT
public:
    ObjetoFisico();
    virtual ~ObjetoFisico();
    virtual void init(dWorldID *world, dSpaceID *space);
    virtual void remove();
    virtual void odeLoop();
    virtual bool odeCollide(dGeomID o1, dGeomID o2);
    virtual void pintar(QPainter *p);
    virtual void lock();
    virtual void unlock();
    QMutex mutex;
    bool isOdeInit;
};

#endif // OBJETOFISICO_H
