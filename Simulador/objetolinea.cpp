#include "objetolinea.h"

ObjetoLinea::ObjetoLinea(QPointF inicio_, QPointF fin_)
{
    inicio = inicio_;
    fin = fin_;
}

ObjetoLinea::~ObjetoLinea() {

}

void ObjetoLinea::init(dWorldID *world, dSpaceID *space) {
    geom = dCreateBox (*space, fabs(inicio.x()-fin.x()), fabs(inicio.y()-fin.y()), 1); // centro en 0 y con largos especificados
    dGeomSetPosition(geom, (inicio.x()+fin.x()) / 2.0, (inicio.y()+fin.y()) / 2.0, 0); // moviendo el centro
    ObjetoFisico::init(world, space);
}

void ObjetoLinea::pintar(QPainter *p) {
    p->drawRect(QRectF((inicio.x()+fin.x()) / 2.0 - fabs(inicio.x()-fin.x()) / 2.0, // centro menos mitad
                (inicio.y()+fin.y()) / 2.0 - fabs(inicio.y()-fin.y()) / 2.0, // centro menos mitad
                fabs(inicio.x()-fin.x()), // largo
                fabs(inicio.y()-fin.y()))); // largo
}
