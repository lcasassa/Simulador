#ifndef TRAINER_H
#define TRAINER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "objetofisico.h"

class Trainer : public QThread
{
    Q_OBJECT
public:
    explicit Trainer(QObject *parent = 0);
    ~Trainer();
    void reset();
    void play();
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
    void playOde();
    void stopOde();
    void pauseOde();
    void resetOde();
    void stepOde(int value);
    void registrarObjetoSimulador(ObjetoFisico * objetoFisico);
    void desregistrarObjetoSimulador(ObjetoFisico * objetoFisico);
    
public slots:
    void odeCommandDone();
    
};

#endif // TRAINER_H
