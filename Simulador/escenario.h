#ifndef ESCENARIO_H
#define ESCENARIO_H

class Escenario
{
public:
    Escenario();
    virtual void registrarObjetos() = 0;
    virtual void desregistrarObjetos() = 0;
};

#endif // ESCENARIO_H
