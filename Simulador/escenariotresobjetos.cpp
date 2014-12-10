#include "escenariotresobjetos.h"
#include "trainer.h"
#include "objetocircunferencia.h"
#include "objetolinea.h"

float xForce_tres_objetos(float tiempo) {
    return 10*cos((float)((int)tiempo%(2*3141))/1000.0)*0.003;
}

float yForce_tres_objetos(float tiempo) {
    return -6*sin((float)((int)tiempo%(2*3141))/1000.0)*0.01 + 4*sin((float)((int)tiempo%(3*3141))/1000.0)*0.01;
}

EscenarioTresObjetos::EscenarioTresObjetos(Trainer *t_) {
    t=t_;
    objetoCircunferencia[0] = new ObjetoCircunferencia(0.5, 1, 0.3, 0, 2,  0, xForce_tres_objetos, yForce_tres_objetos);
    objetoCircunferencia[1] = new ObjetoCircunferencia(0.5, 1, 0.3, 2, 0);
    objetoCircunferencia[2] = new ObjetoCircunferencia(0.5, 1, 0.3, 0,-2);

    qreal ancho=0.1, largo=4.5;
    objetoLinea = new ObjetoLinea(QPointF(-largo/2,-largo/2), QPointF( -largo/2-ancho, largo/2)); // centro
}

EscenarioTresObjetos::~EscenarioTresObjetos() {
    for(int i=0; i<3; i++) {
        delete objetoCircunferencia[i];
    }
    delete objetoLinea;
}

void EscenarioTresObjetos::registrarObjetos() {
    for(int i=0; i<3; i++) {
        t->registrarObjeto( objetoCircunferencia[i] );
    }
    t->registrarObjeto(objetoLinea);
}

void EscenarioTresObjetos::desregistrarObjetos() {
    for(int i=0; i<3; i++) {
        t->desregistrarObjeto( objetoCircunferencia[i] );
    }
    t->desregistrarObjeto(objetoLinea);
}
