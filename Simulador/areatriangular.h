#ifndef AREATRIANGULAR_H
#define AREATRIANGULAR_H

#include <QObject>
#include <QPainter>
#include <ode/ode.h>

class AreaTriangular : public QObject
{
    Q_OBJECT
public:
    explicit AreaTriangular(QObject *parent = 0);
    ~AreaTriangular();
    void setTriangulo(dReal base1X, dReal base2X, dReal puntaX, dReal puntaY = 1.0);
    dReal evalua(dReal x);
    void pintar(QPainter *p);

signals:
    
public slots:

private:
    dReal base1[2];
    dReal base2[2];
    dReal punta[2];
    dReal entrada;
    dReal salida;
};

#endif // AREATRIANGULAR_H
