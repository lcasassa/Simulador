#include "escenariounobjeto.h"
#include "trainer.h"
#include "objetocircunferencia.h"
#include "objetolinea.h"

EscenarioUnObjeto::EscenarioUnObjeto(Trainer *t_) :
    Escenario()
{
    t=t_;
    objetoCircunferencia = new ObjetoCircunferencia(0.5,1,0.3, 0,-2);

    //qreal ancho=0.1, largo=4.5;
    //objetoLinea = new ObjetoLinea(QPointF(-largo/2,-largo/2), QPointF( -largo/2-ancho, largo/2)); // centro
}

EscenarioUnObjeto::~EscenarioUnObjeto() {
    delete objetoCircunferencia;
    //delete objetoLinea;
}

void EscenarioUnObjeto::registrarObjetos() {
    t->registrarObjeto(objetoCircunferencia);
    //t->registrarObjeto(objetoLinea);
}

void EscenarioUnObjeto::desregistrarObjetos() {
    t->desregistrarObjeto(objetoCircunferencia);
    //t->desregistrarObjeto(objetoLinea);
}

