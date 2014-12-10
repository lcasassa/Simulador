#include "escenariotresobjetoscerca.h"
#include "trainer.h"
#include "objetocircunferencia.h"
#include "objetolinea.h"

float xForce_tres_objetos_cerca(float tiempo) {
    return 20*cos((float)((int)tiempo%(2*3141))/1000.0)*0.003;
}

float yForce_tres_objetos_cerca(float tiempo) {
    return -10*sin((float)((int)tiempo%(2*3141))/1000.0)*0.01;
}

EscenarioTresObjetosCerca::EscenarioTresObjetosCerca(Trainer *t_) {
    t=t_;
    objetoCircunferencia[0] = new ObjetoCircunferencia(0.5,1,0.3, 0, 1.8, 0, xForce_tres_objetos_cerca, yForce_tres_objetos_cerca);
    objetoCircunferencia[1] = new ObjetoCircunferencia(0.5,1,0.3, 1.3, 0);
    objetoCircunferencia[2] = new ObjetoCircunferencia(0.5,1,0.3, 0,-1.8);

    //qreal ancho=0.1, largo=4.5;
    //objetoLinea = new ObjetoLinea(QPointF(-largo/2,-largo/2), QPointF( -largo/2-ancho, largo/2)); // centro
}

EscenarioTresObjetosCerca::~EscenarioTresObjetosCerca() {
    for(int i=0; i<3; i++) {
        delete objetoCircunferencia[i];
    }
    //delete objetoLinea;
}

void EscenarioTresObjetosCerca::registrarObjetos() {
    for(int i=0; i<3; i++) {
        t->registrarObjeto( objetoCircunferencia[i] );
    }
    //t->registrarObjeto(objetoLinea);
}

void EscenarioTresObjetosCerca::desregistrarObjetos() {
    for(int i=0; i<3; i++) {
        t->desregistrarObjeto( objetoCircunferencia[i] );
    }
    //t->desregistrarObjeto(objetoLinea);
}
