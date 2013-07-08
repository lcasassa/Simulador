#ifndef CONTROLFUZZY_H
#define CONTROLFUZZY_H

#include "control.h"
#include "fuzzyficacion.h"

class ControlFuzzy : public Control
{
    Q_OBJECT
public:
    explicit ControlFuzzy(Fuzzyficacion *fuzzyficacion_, QWidget *parent = 0);
    ~ControlFuzzy();
    void loopControl(qreal distancia_[4*4], qreal vel_[4*4], qreal out_[2]);
    void pintar(QPainter *p);
    
signals:
    
public slots:
private:
    Fuzzyficacion *fuzzyficacion;
    
};

#endif // CONTROLFUZZY_H
