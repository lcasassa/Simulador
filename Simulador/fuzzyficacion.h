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
    void evaluar(qreal distancia_[4*4], qreal vel_[4*4], qreal out_[2]);
    float fuzzyfica(float distance_, float vel_);
    ~Fuzzyficacion();
//    void pintar(QPainter *p);
//    void addAreaTriangular(QString nombre_, qreal base1_, qreal base2_, qreal punta_);
//    void addAreaTriangular(QString nombre_, qreal base1_, qreal base2_);

signals:
    
public slots:
    
private:
    fl::FuzzyEngine* model;
    fl::InputLVar* distance;
    fl::InputLVar* vel;
    fl::OutputLVar* out;

//    QList<AreaTriangular *> areaTriangular;
};

#endif // FUZZYFICACION_H
