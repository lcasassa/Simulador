#ifndef ESCENARIOUNOBJETO_H
#define ESCENARIOUNOBJETO_H

#include "escenario.h"
class Trainer;
class ObjetoCircunferencia;
class ObjetoLinea;

class EscenarioUnObjeto : public Escenario
{
public:
    EscenarioUnObjeto(Trainer *t_);
    ~EscenarioUnObjeto();
    void registrarObjetos();
    void desregistrarObjetos();
private:
    //ObjetoLinea* objetoLinea;
    ObjetoCircunferencia* objetoCircunferencia;
    Trainer *t;

};

#endif // ESCENARIOUNOBJETO_H
