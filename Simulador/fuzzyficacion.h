#ifndef FUZZYFICACION_H
#define FUZZYFICACION_H

#include <QObject>
#include <QList>
//#include "areatriangular.h"

//#include <ode/ode.h>
#include <fuzzylite/FuzzyLite.h>

class Fuzzyficacion : public QObject
{
    Q_OBJECT
public:
    explicit Fuzzyficacion(QObject *parent = 0);
    void evaluar(qreal *distanciaDetectado, qreal *salidas);
    ~Fuzzyficacion();
//    void pintar(QPainter *p);
//    void addAreaTriangular(QString nombre_, qreal base1_, qreal base2_, qreal punta_);
//    void addAreaTriangular(QString nombre_, qreal base1_, qreal base2_);

signals:
    
public slots:
    
private:
    fl::FuzzyEngine* model;
    fl::InputLVar* energy;
    fl::OutputLVar* health;

//    QList<AreaTriangular *> areaTriangular;
};

#endif // FUZZYFICACION_H
