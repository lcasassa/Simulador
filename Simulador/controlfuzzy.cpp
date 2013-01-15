#include "controlfuzzy.h"

ControlFuzzy::ControlFuzzy(QObject *parent) :
    Control(parent)
{
}

ControlFuzzy::~ControlFuzzy() {

}

void ControlFuzzy::loopControl(dReal *distanciaDetectado, dReal *salidas) {
    salidas[0] = distanciaDetectado[0] - 1.0;
}
