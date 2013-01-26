#include "areatriangular.h"
#include <QDebug>

int AreaTriangular::id_count = 0;

AreaTriangular::AreaTriangular(QObject *parent) :
    QObject(parent)
{
    id = id_count++;
}

AreaTriangular::~AreaTriangular() {

}

void AreaTriangular::setTriangulo(QString nombre_, qreal base1_, qreal base2_) {
    setTriangulo(nombre_, base1_, base2_, QPointF((base1_ + base2_)/2, 1));
}

void AreaTriangular::setTriangulo(QString nombre_, qreal base1_, qreal base2_, qreal punta_) {
    setTriangulo(nombre_, base1_, base2_, QPointF(punta_, 1));
}

void AreaTriangular::setTriangulo(QString nombre_, qreal base1_, qreal base2_, QPointF punta_) {
    nombre = nombre_;
    base1.setX(base1_); // .2
    base1.setY(0.0);
    base2.setX(base2_); // .8
    base2.setY(0.0);
    punta = punta_; // .5

    qWarning() << base1;
    qWarning() << base2;
    qWarning() << punta;
}

dReal AreaTriangular::evalua(dReal x) {
    dReal m;
    entrada = x;
    if(x < base1.x()) {
        salida = 0.0;
    } else if(x < punta.x()) { // entre base1 y punta
        m = (punta.y() - base1.y()) / (punta.x() - base1.x());
        salida = m*(x - base1.x()) + base1.y();
    } else if(x < base2.x()) { // entre punta y base2
        m = (base2.y() - punta.y()) / (base2.x() - punta.x());
        salida = m*(x - punta.x()) + punta.y();
    } else {
        salida = 0.0;
    }
    return salida;
}

void AreaTriangular::pintar(QPainter *p) {

    QPen pen = p->pen();
    QBrush brush = p->brush();

    p->setPen(Qt::black);
    switch(id) {
    case 0:
        p->setBrush(QBrush(Qt::red));
        break;
    case 1:
        p->setBrush(QBrush(Qt::yellow));
        break;
    }

    QPointF points[3] = {
        base1,
        base2,
        punta
    };
    p->drawPolygon(points, 3);
//    p->drawRect(QRectF(0,0,1,10)); // largo

//    qWarning("%f => %f", entrada, salida);

    p->setPen(pen);
    p->setBrush(brush);

}








