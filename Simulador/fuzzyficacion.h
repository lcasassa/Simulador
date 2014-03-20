#ifndef FUZZYFICACION_H
#define FUZZYFICACION_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QMetaType>
//#include "areatriangular.h"

//#include <ode/ode.h>
#include <fl/Headers.h>

struct fuzzy {
    double input1[3][2];
    double input2[3][2];
    double output[4][2];

};
Q_DECLARE_METATYPE(fuzzy)

class Fuzzyficacion : public QObject
{
    Q_OBJECT
public:
    explicit Fuzzyficacion(QObject *parent = 0);
    void evaluar(qreal distancia_[4*4], qreal vel_[4*4], qreal out_[2]);
    float fuzzyfica(float distancia_, float vel_);
    void setFuzzy(fuzzy &f);
    ~Fuzzyficacion();
    //static QByteArray serialize(struct fuzzy f);
//    void pintar(QPainter *p);
//    void addAreaTriangular(QString nombre_, qreal base1_, qreal base2_, qreal punta_);
//    void addAreaTriangular(QString nombre_, qreal base1_, qreal base2_);

signals:
    
public slots:
    
private:
    fl::Engine* engine;
    fl::InputVariable* distancia;
    fl::InputVariable* vel;
    fl::OutputVariable* out;
//    QList<AreaTriangular *> areaTriangular;
};

#endif // FUZZYFICACION_H
