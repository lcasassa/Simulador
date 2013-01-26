#ifndef CONTROLFUZZY_H
#define CONTROLFUZZY_H

#include "control.h"
#include "fuzzyficacion.h"

class ControlFuzzy : public Control
{
    Q_OBJECT
public:
    explicit ControlFuzzy(QWidget *parent = 0);
    ~ControlFuzzy();
    void loopControl(qreal *distanciaDetectado, qreal *salidas);
    void pintar(QPainter *p);
    void evaluar(qreal *distanciaDetectado, qreal *salidas);
    
signals:
    
public slots:
private:
    Fuzzyficacion fuzzyficacion;
    
};

#endif // CONTROLFUZZY_H
