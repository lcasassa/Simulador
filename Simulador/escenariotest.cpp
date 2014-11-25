#include "escenariotest.h"
#include "trainer.h"
#include "objetocircunferencia.h"
#include "objetolinea.h"

float xForce(float tiempo) {
    return 10*cos((float)((int)tiempo%(2*3141))/1000.0)*0.01;
}

float yForce(float tiempo) {
    return 10*sin((float)((int)tiempo%(2*3141))/1000.0)*0.01;
}

EscenarioTest::EscenarioTest(Trainer *t_) {
    t=t_;
    objetoCircunferencia[0] = new ObjetoCircunferencia(0.4,0.86,0.3, 0, 1.2);
    objetoCircunferencia[1] = new ObjetoCircunferencia(0.6,0.7,0.3, 2, 0, 0, xForce, yForce);
    objetoCircunferencia[2] = new ObjetoCircunferencia(0.5,1,0.3, 0,-2);

    qreal ancho=0.1, largo=4.5;
    objetoLinea = new ObjetoLinea(QPointF(-largo/2,-largo/2), QPointF( -largo/2-ancho, largo/2)); // centro
}

EscenarioTest::~EscenarioTest() {
    for(int i=0; i<3; i++) {
        delete objetoCircunferencia[i];
    }
    delete objetoLinea;
}

void EscenarioTest::registrarObjetos() {
    for(int i=0; i<3; i++) {
        t->registrarObjeto( objetoCircunferencia[i] );
    }
    t->registrarObjeto(objetoLinea);
}

void EscenarioTest::desregistrarObjetos() {
    for(int i=0; i<3; i++) {
        t->desregistrarObjeto( objetoCircunferencia[i] );
    }
    t->desregistrarObjeto(objetoLinea);
}




float xForce2(float tiempo) {
    return 0.1;
}

float yForce2(float tiempo) {
    return -0.1;
}

EscenarioTest2::EscenarioTest2(Trainer *t_) {
    t=t_;
    objetoCircunferencia[0] = new ObjetoCircunferencia(0.4,0.8,0.3, 0, 2, 0, xForce2, yForce2);
    objetoCircunferencia[1] = new ObjetoCircunferencia(0.6,0.8,0.3, 2, 0, 0, xForce2, yForce2);
    objetoCircunferencia[2] = new ObjetoCircunferencia(0.5,1,0.3, 0,-2, 0, xForce2, yForce2);

    qreal ancho=0.1, largo=4.5;
    objetoLinea = new ObjetoLinea(QPointF(-largo/2,-largo/2), QPointF( -largo/2-ancho, largo/2)); // centro
}

EscenarioTest2::~EscenarioTest2() {
    for(int i=0; i<3; i++) {
        delete objetoCircunferencia[i];
    }
    delete objetoLinea;
}

void EscenarioTest2::registrarObjetos() {
    for(int i=0; i<3; i++) {
        t->registrarObjeto( objetoCircunferencia[i] );
    }
    t->registrarObjeto(objetoLinea);
}

void EscenarioTest2::desregistrarObjetos() {
    for(int i=0; i<3; i++) {
        t->desregistrarObjeto( objetoCircunferencia[i] );
    }
    t->desregistrarObjeto(objetoLinea);
}




float xForce3(float tiempo) {
    return 40*cos((float)((int)tiempo%(1*3141))/1000.0)*0.003;
}

float yForce3(float tiempo) {
    return 40*cos((float)((int)tiempo%(1*3141))/1000.0)*0.003;
}

EscenarioTest3::EscenarioTest3(Trainer *t_) {
    t=t_;
    objetoCircunferencia[0] = new ObjetoCircunferencia(0.4,0.8,0.3, 0, 2, 0, xForce3, yForce3);
    objetoCircunferencia[1] = new ObjetoCircunferencia(0.6,0.8,0.3, 2, 0, 0, xForce3, yForce3);
    objetoCircunferencia[2] = new ObjetoCircunferencia(0.5,1,0.3, 0,-2, 0, xForce3, yForce3);

    qreal ancho=0.1, largo=4.5;
    objetoLinea = new ObjetoLinea(QPointF(-largo/2,-largo/2), QPointF( -largo/2-ancho, largo/2)); // centro
}

EscenarioTest3::~EscenarioTest3() {
    for(int i=0; i<3; i++) {
        delete objetoCircunferencia[i];
    }
    delete objetoLinea;
}

void EscenarioTest3::registrarObjetos() {
    for(int i=0; i<3; i++) {
        t->registrarObjeto( objetoCircunferencia[i] );
    }
    t->registrarObjeto(objetoLinea);
}

void EscenarioTest3::desregistrarObjetos() {
    for(int i=0; i<3; i++) {
        t->desregistrarObjeto( objetoCircunferencia[i] );
    }
    t->desregistrarObjeto(objetoLinea);
}


float xForce4(float tiempo) {
    return 40*cos((float)((int)tiempo%(1*3141))/1000.0)*0.003;
}

float yForce4(float tiempo) {
    return 40*cos((float)((int)tiempo%(3*3141))/1000.0)*0.003;
}

EscenarioTest4::EscenarioTest4(Trainer *t_) {
    t=t_;
    objetoCircunferencia[0] = new ObjetoCircunferencia(0.4,0.8,0.3, 0, 2, 0, xForce4, yForce4);
    objetoCircunferencia[1] = new ObjetoCircunferencia(0.6,0.8,0.3, 2, 0, 0, xForce4, yForce4);
    objetoCircunferencia[2] = new ObjetoCircunferencia(0.5,1,0.3, 0,-2, 0, xForce4, yForce4);

    qreal ancho=0.1, largo=4.5;
    objetoLinea = new ObjetoLinea(QPointF(-largo/2,-largo/2), QPointF( -largo/2-ancho, largo/2)); // centro
}

EscenarioTest4::~EscenarioTest4() {
    for(int i=0; i<3; i++) {
        delete objetoCircunferencia[i];
    }
    delete objetoLinea;
}

void EscenarioTest4::registrarObjetos() {
    for(int i=0; i<3; i++) {
        t->registrarObjeto( objetoCircunferencia[i] );
    }
    t->registrarObjeto(objetoLinea);
}

void EscenarioTest4::desregistrarObjetos() {
    for(int i=0; i<3; i++) {
        t->desregistrarObjeto( objetoCircunferencia[i] );
    }
    t->desregistrarObjeto(objetoLinea);
}



float xForce5a(float tiempo) {
    return -40*cos((float)((int)tiempo%(2*3141))/1000.0)*0.003;
}

float yForce5a(float tiempo) {
    return -40*sin((float)((int)tiempo%(3*3141))/1000.0)*0.003;
}

float xForce5b(float tiempo) {
    return 40*cos((float)((int)tiempo%(1*3141))/1000.0)*0.003;
}

float yForce5b(float tiempo) {
    return 40*cos((float)((int)tiempo%(3*3141))/1000.0)*0.003;
}

float xForce5c(float tiempo) {
    return -40*cos((float)((int)tiempo%(1*3141))/1000.0)*0.003;
}

float yForce5c(float tiempo) {
    return -40*sin((float)((int)tiempo%(3*3141))/1000.0)*0.003;
}

EscenarioTest5::EscenarioTest5(Trainer *t_) {
    t=t_;
    objetoCircunferencia[0] = new ObjetoCircunferencia(0.4,0.8,0.3, 0, 2, 0, xForce5a, yForce5a);
    objetoCircunferencia[1] = new ObjetoCircunferencia(0.6,0.8,0.3, 2, 0, 0, xForce5b, yForce5b);
    objetoCircunferencia[2] = new ObjetoCircunferencia(0.5,1,0.3, 0,-2, 0, xForce5c, yForce5c);

    qreal ancho=0.1, largo=4.5;
    objetoLinea = new ObjetoLinea(QPointF(-largo/2,-largo/2), QPointF( -largo/2-ancho, largo/2)); // centro
}

EscenarioTest5::~EscenarioTest5() {
    for(int i=0; i<3; i++) {
        delete objetoCircunferencia[i];
    }
    delete objetoLinea;
}

void EscenarioTest5::registrarObjetos() {
    for(int i=0; i<3; i++) {
        t->registrarObjeto( objetoCircunferencia[i] );
    }
    t->registrarObjeto(objetoLinea);
}

void EscenarioTest5::desregistrarObjetos() {
    for(int i=0; i<3; i++) {
        t->desregistrarObjeto( objetoCircunferencia[i] );
    }
    t->desregistrarObjeto(objetoLinea);
}
