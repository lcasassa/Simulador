#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <ode/ode.h>

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    virtual ~Control();
    virtual void loopControl(dReal *distanciaDetectado, dReal *salidas);
signals:
    
public slots:
    
};

#endif // CONTROL_H
