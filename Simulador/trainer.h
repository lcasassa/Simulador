#ifndef TRAINER_H
#define TRAINER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "objetofisico.h"
#include "fuzzyficacion.h"
//#include "simulador.h"
class Simulador;

class Trainer : public QThread
{
    Q_OBJECT
public:
    explicit Trainer(Simulador *sim_, QObject *parent = 0);
    ~Trainer();
    void reset();
    void play(double sec);
    void stop();
    void delOde();
    void pause();
    void step(int value);
    void registrarObjeto(ObjetoFisico * objetoFisico);
    void desregistrarObjeto(ObjetoFisico * objetoFisico);

    Simulador *sim;

protected:
    virtual void run() = 0;

signals:
    void playOde(double);
    void stopOde();
    void destroyOde();
    void pauseOde();
    void resetOde();
    void stepOde(int value);
    void registrarObjetoSimulador(ObjetoFisico * objetoFisico);
    void desregistrarObjetoSimulador(ObjetoFisico * objetoFisico);
    void newFuzzy(fuzzy f, bool setSpinBox);
    void bestFuzzy(fuzzy f);
    
};

#endif // TRAINER_H
