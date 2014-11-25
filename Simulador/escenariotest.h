#ifndef ESCENARIOTEST_H
#define ESCENARIOTEST_H

#include "escenario.h"

class Trainer;
class ObjetoCircunferencia;
class ObjetoLinea;

class EscenarioTest : public Escenario
{
public:
    EscenarioTest(Trainer *t_);
    ~EscenarioTest();
    void registrarObjetos();
    void desregistrarObjetos();
private:
    ObjetoLinea* objetoLinea;
    ObjetoCircunferencia* objetoCircunferencia[3];
    Trainer *t;
};

class EscenarioTest2 : public Escenario
{
public:
    EscenarioTest2(Trainer *t_);
    ~EscenarioTest2();
    void registrarObjetos();
    void desregistrarObjetos();
private:
    ObjetoLinea* objetoLinea;
    ObjetoCircunferencia* objetoCircunferencia[3];
    Trainer *t;
};

class EscenarioTest3 : public Escenario
{
public:
    EscenarioTest3(Trainer *t_);
    ~EscenarioTest3();
    void registrarObjetos();
    void desregistrarObjetos();
private:
    ObjetoLinea* objetoLinea;
    ObjetoCircunferencia* objetoCircunferencia[3];
    Trainer *t;
};

class EscenarioTest4 : public Escenario
{
public:
    EscenarioTest4(Trainer *t_);
    ~EscenarioTest4();
    void registrarObjetos();
    void desregistrarObjetos();
private:
    ObjetoLinea* objetoLinea;
    ObjetoCircunferencia* objetoCircunferencia[3];
    Trainer *t;
};

class EscenarioTest5 : public Escenario
{
public:
    EscenarioTest5(Trainer *t_);
    ~EscenarioTest5();
    void registrarObjetos();
    void desregistrarObjetos();
private:
    ObjetoLinea* objetoLinea;
    ObjetoCircunferencia* objetoCircunferencia[3];
    Trainer *t;
};

#endif // ESCENARIOTRESOBJETOS_H
