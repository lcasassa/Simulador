#ifndef ESCENARIOTRESOBJETOSCERCA_H
#define ESCENARIOTRESOBJETOSCERCA_H

#include "escenario.h"

class Trainer;
class ObjetoCircunferencia;
class ObjetoLinea;

class EscenarioTresObjetosCerca : public Escenario
{
public:
    EscenarioTresObjetosCerca(Trainer *t_);
    ~EscenarioTresObjetosCerca();
    void registrarObjetos();
    void desregistrarObjetos();
private:
    ObjetoLinea* objetoLinea;
    ObjetoCircunferencia* objetoCircunferencia[3];
    Trainer *t;
};

#endif // ESCENARIOTRESOBJETOSCERCA_H
