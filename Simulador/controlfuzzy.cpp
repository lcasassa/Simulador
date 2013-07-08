#include "controlfuzzy.h"

ControlFuzzy::ControlFuzzy(Fuzzyficacion *fuzzyficacion_, QWidget *parent) :
    Control(parent)
{
    fuzzyficacion = fuzzyficacion_;
//    fuzzyficacion.addAreaTriangular("Caquita", 0.2, 0.5);
//    fuzzyficacion.addAreaTriangular("Caquita2", 0.5, 0.8);

}

ControlFuzzy::~ControlFuzzy() {

}

void ControlFuzzy::loopControl(qreal distancia_[4*4], qreal vel_[4*4], qreal out_[2]) {
    fuzzyficacion->evaluar(distancia_, vel_, out_);
}

void ControlFuzzy::pintar(QPainter *p) {
    //fuzzyficacion.pintar(p);
}
