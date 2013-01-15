#ifndef CONTROLFUZZY_H
#define CONTROLFUZZY_H

#include "control.h"

class ControlFuzzy : public Control
{
    Q_OBJECT
public:
    explicit ControlFuzzy(QObject *parent = 0);
    ~ControlFuzzy();
    void loopControl(dReal *distanciaDetectado, dReal *salidas);
    
signals:
    
public slots:
    
};

#endif // CONTROLFUZZY_H
