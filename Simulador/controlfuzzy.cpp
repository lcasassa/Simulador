#include "controlfuzzy.h"

ControlFuzzy::ControlFuzzy(QWidget *parent) :
    Control(parent)
{
//    fuzzyficacion.addAreaTriangular("Caquita", 0.2, 0.5);
//    fuzzyficacion.addAreaTriangular("Caquita2", 0.5, 0.8);

}

ControlFuzzy::~ControlFuzzy() {

}

void ControlFuzzy::loopControl(qreal *distanciaDetectado, qreal *salidas) {
//    salidas[0] = distanciaDetectado[0] - 1.0;
    static int i = 0;
    if(i<10) { i++; return; }
    fuzzyficacion.evaluar(distanciaDetectado, salidas);
//    qWarning("i:%f o:%f", distanciaDetectado[0], salidas[0]);
}

void ControlFuzzy::pintar(QPainter *p) {
    //fuzzyficacion.pintar(p);
}
