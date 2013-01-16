#include "areatriangular.h"

AreaTriangular::AreaTriangular(QObject *parent) :
    QObject(parent)
{
}


AreaTriangular::~AreaTriangular() {

}

void AreaTriangular::setTriangulo(dReal base1X, dReal base2X, dReal puntaX, dReal puntaY) {
    base1[0] = base1X; // .2
    base1[1] = 0.0;
    base2[0] = base2X; // .8
    base2[1] = 0.0;
    punta[0] = puntaX; // .5
    punta[1] = puntaY; // 1
}

dReal AreaTriangular::evalua(dReal x) {
    dReal m;
    entrada = x;
    if(x < base1[0]) {
        salida = 0.0;
    } else if(x < punta[0]) { // entre base1 y punta
        m = (punta[1] - base1[1]) / (punta[0] - base1[0]);
        salida = m*(x - base1[0]) + base1[1];
    } else if(x < base2[0]) { // entre punta y base2
        m = (base2[1] - punta[1]) / (base2[0] - punta[0]);
        salida = m*(x - punta[0]) + punta[1];
    } else {
        salida = 0.0;
    }
    return salida;
}

void AreaTriangular::pintar(QPainter *p) {
    qWarning("%f => %f", entrada, salida);
}
