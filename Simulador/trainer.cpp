#include "trainer.h"
#include "objetocircunferencia.h"
#include "robotquadrotor.h"
#include "fuzzyficacion.h"

#define DEBUG_TRAINER 1

Trainer::Trainer(QObject *parent) :
    QThread(parent)
{
}

Trainer::~Trainer() {

}

void Trainer::reset() {
#ifdef DEBUG_TRAINER_2
    qWarning("Trainer: Reset");
#endif
    emit resetOde();
    odeCommandWaitCondition.wait(&odeCommandMutex);
#ifdef DEBUG_TRAINER
    qWarning("Trainer: Reset OK");
#endif
}

void Trainer::stop() {
#ifdef DEBUG_TRAINER_2
    qWarning("Trainer: Stop");
#endif
    emit stopOde();
    odeCommandWaitCondition.wait(&odeCommandMutex);
#ifdef DEBUG_TRAINER
    qWarning("Trainer: Stop OK");
#endif
}

void Trainer::play() {
#ifdef DEBUG_TRAINER_2
    qWarning("Trainer: Play");
#endif
    emit playOde();
    odeCommandWaitCondition.wait(&odeCommandMutex);
#ifdef DEBUG_TRAINER
    qWarning("Trainer: Play OK");
#endif
}

void Trainer::pause() {
#ifdef DEBUG_TRAINER_2
    qWarning("Trainer: Pause");
#endif
    emit pauseOde();
    odeCommandWaitCondition.wait(&odeCommandMutex);
#ifdef DEBUG_TRAINER
    qWarning("Trainer: Pause OK");
#endif
}

void Trainer::step(int value) {
#ifdef DEBUG_TRAINER_2
    qWarning("Trainer: Step %d", value);
#endif
    emit stepOde(value);
    //odeCommandWaitCondition.wait(&odeCommandMutex);
    msleep(2000);
#ifdef DEBUG_TRAINER
    qWarning("Trainer: Step OK");
#endif
}

void Trainer::registrarObjeto(ObjetoFisico * objetoFisico) {
    emit registrarObjetoSimulador(objetoFisico);
    odeCommandWaitCondition.wait(&odeCommandMutex);
#ifdef DEBUG_TRAINER2
    qWarning("Trainer: registrarObjeto OK");
#endif
}

void Trainer::desregistrarObjeto(ObjetoFisico * objetoFisico) {
    emit desregistrarObjetoSimulador(objetoFisico);
    odeCommandWaitCondition.wait(&odeCommandMutex);
#ifdef DEBUG_TRAINER2
    qWarning("Trainer: desregistrarObjeto OK");
#endif
}

void Trainer::odeCommandDone() {
    odeCommandWaitCondition.wakeAll();
}
