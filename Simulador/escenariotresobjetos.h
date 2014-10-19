#ifndef ESCENARIOTRESOBJETOS_H
#define ESCENARIOTRESOBJETOS_H

#include "escenario.h"

class Trainer;
class ObjetoCircunferencia;
class ObjetoLinea;

class EscenarioTresObjetos : public Escenario
{
public:
    EscenarioTresObjetos(Trainer *t_);
    ~EscenarioTresObjetos();
    void registrarObjetos();
    void desregistrarObjetos();
private:
    ObjetoLinea* objetoLinea;
    ObjetoCircunferencia* objetoCircunferencia[3];
    Trainer *t;
};

#endif // ESCENARIOTRESOBJETOS_H
