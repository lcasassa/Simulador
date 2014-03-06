#ifndef TRAINER_H
#define TRAINER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "objetofisico.h"
#include <fuzzyficacion.h>

class Trainer : public QThread
{
    Q_OBJECT
public:
    explicit Trainer(QObject *parent = 0);
    ~Trainer();
    void reset();
    void play(double sec);
    void stop();
    void pause();
    void step(int value);
    void registrarObjeto(ObjetoFisico * objetoFisico);
    void desregistrarObjeto(ObjetoFisico * objetoFisico);

protected:
    virtual void run() = 0;
    QMutex odeCommandMutex;
    QWaitCondition odeCommandWaitCondition;

signals:
    void playOde(double);
    void stopOde();
    void pauseOde();
    void resetOde();
    void stepOde(int value);
    void registrarObjetoSimulador(ObjetoFisico * objetoFisico);
    void desregistrarObjetoSimulador(ObjetoFisico * objetoFisico);
    void newFuzzy(fuzzy f);
    
public slots:
    void odeCommandDone();
    
};

#endif // TRAINER_H
