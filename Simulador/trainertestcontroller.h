#ifndef TRAINERTESTCONTROLLER_H
#define TRAINERTESTCONTROLLER_H

#include "trainer.h"
#include <vector>
#include <QFile>

class Escenario;

class TrainerTestController : public Trainer
{
    Q_OBJECT
public:
    TrainerTestController(Simulador *sim_, QObject *parent = 0);
    float doSimulation(fuzzy &b);
    float simulate(Escenario &e, fuzzy &b, double time);

protected:
    void run();

private:
    QFile file;

};

#endif // TRAINERTESTCONTROLLER_H
