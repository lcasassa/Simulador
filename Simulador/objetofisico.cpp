#include "objetofisico.h"

ObjetoFisico::ObjetoFisico()
{
}

void ObjetoFisico::init(dWorldID *world, dSpaceID *space) {

}

void ObjetoFisico::odeLoop() {

}

bool ObjetoFisico::odeCollide(dGeomID o1, dGeomID o2) {
    return false;
}

void ObjetoFisico::pintar(QPainter *p) {

}

void ObjetoFisico::lock() {
    mutex.lock();
}

void ObjetoFisico::unlock() {
    mutex.unlock();
}
