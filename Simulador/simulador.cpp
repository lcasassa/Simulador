#include "simulador.h"
#include "traineralgoritmogenetico.h"
#include <QPainter>
#include <QTimer>

//#define DEBUG_SIMULADOR 1

Simulador::Simulador(QWidget *parent) :
    QWidget(parent)
{

#ifdef DEBUG_SIMULADOR
    qWarning("new Ode()");
#endif
    ode = new Ode(this);
//    QTimer::singleShot(100, this, SLOT(timeout()));

    timer = new QTimer();
    setRefrescoHz(30);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeout()));

#ifdef DEBUG_SIMULADOR
    qWarning("new Trainer()");
#endif
    trainer = new TrainerAlgoritmoGenetico(this);

    connect(trainer, SIGNAL(playOde(double)),  this, SLOT(play(double)));
    connect(trainer, SIGNAL(stopOde()),  this, SLOT(stop()));
    connect(trainer, SIGNAL(resetOde()), this, SLOT(reset()));
    connect(trainer, SIGNAL(pauseOde()), this, SLOT(pause()));
    connect(trainer, SIGNAL(stepOde(int)), this, SLOT(step(int)));
    connect(trainer, SIGNAL(registrarObjetoSimulador(ObjetoFisico*)), this, SLOT(registrarObjeto(ObjetoFisico*)));
    connect(trainer, SIGNAL(desregistrarObjetoSimulador(ObjetoFisico*)), this, SLOT(desregistrarObjeto(ObjetoFisico*)));
    connect(this, SIGNAL(commandDone()), trainer, SLOT(odeCommandDone())); // sync trainer

    plotFuzzyInput = NULL;
    plotFuzzyOutput = NULL;
    connect(trainer, SIGNAL(newFuzzy(fuzzy)), this, SLOT(newFuzzy(fuzzy)));

}

void Simulador::setFuzzyWidgets(PlotFuzzy *plotFuzzyInput_, PlotFuzzy *plotFuzzyOutput_) {
    plotFuzzyInput = plotFuzzyInput_;
    plotFuzzyOutput = plotFuzzyOutput_;
}

void Simulador::newFuzzy(fuzzy f) {
    if(plotFuzzyInput == NULL || plotFuzzyOutput == NULL)
        return;

    //plotFuzzyInput->lines.append(QLine(0,0,100,100));
    //plotFuzzyInput->lines.append(QLine(0,0,-100,100));

    return;

}

Simulador::~Simulador() {
    stop();

    listaObjetoFisicoMutex.lock();
    listaObjetoFisico.clear();
    listaObjetoFisicoMutex.unlock();

    delete ode;
    delete timer;
}

void Simulador::setRefrescoHz(int refrescoHz) {
    timer->setInterval(1000/refrescoHz);
}

void Simulador::timeout() {
    this->repaint();
}

void Simulador::registrarObjeto(ObjetoFisico *objetoFisico, bool sendCommandDone) {
    listaObjetoFisicoMutex.lock();
    listaObjetoFisico.append(objetoFisico);
    listaObjetoFisicoMutex.unlock();
    if(sendCommandDone)
        emit commandDone();

}

void Simulador::desregistrarObjeto(ObjetoFisico *objetoFisico, bool sendCommandDone) {
    listaObjetoFisicoMutex.lock();
    objetoFisico->remove();
    listaObjetoFisico.removeOne(objetoFisico);
    listaObjetoFisicoMutex.unlock();
    if(sendCommandDone)
        emit commandDone();
}

bool Simulador::playPause() {
    if(timer->isActive())
        pause();
    else
        play(1);

    return timer->isActive();
}

void Simulador::play(double sec, bool sendCommandDone) {
    ode->playOde(sec, sendCommandDone);
    timer->start();
    //if(sendCommandDone)
    //    emit commandDone();
}

void Simulador::step(int steps_) {
    timer->stop();
    ode->stepOde(steps_, true);
    for(int i=0; i<10; i++)
        QTimer::singleShot(100*i, this, SLOT(timeout())); // just in case ode takes more time to solve all the steps
}

void Simulador::odeCommandDone() {
    emit commandDone();
}

void Simulador::pause() {
    ode->pauseOde();
    timer->stop();
    emit commandDone();
}

void Simulador::stop(bool sendCommandDone) {
    timer->stop();
    ode->stopOde();
    ode->wait(3000);
    if(ode->isRunning()) {
        qWarning("Matando al thread");
    }
    if(sendCommandDone)
        emit commandDone();
}

void Simulador::reset() {
    stop(DO_NOT_SEND_SIGNAL_WHEN_DONE);

    listaObjetoFisicoMutex.lock();
    listaObjetoFisico.clear();
    listaObjetoFisicoMutex.unlock();
    delete ode;

    ode = new Ode(this);

    QTimer::singleShot(100, this, SLOT(timeout()));

    while(!ode->isRunning()) ;
    emit commandDone();

}

void Simulador::paintEvent(QPaintEvent *) {

    //qWarning("paint loop");
    QPainter p;
    float radio;

    if(!ode->isRunning()) return;

    radio = (this->width()/this->height()) < 1 ? this->width() : this->height();

    p.begin(this);
    p.translate(radio/2,radio/2);
    p.scale(radio/10.0,radio/-10.0);

    listaObjetoFisicoMutex.lock();
    for (int i = 0; i < listaObjetoFisico.size(); ++i) {
        if(listaObjetoFisico[i]->isOdeInit)
            listaObjetoFisico[i]->pintar(&p);
    }
    listaObjetoFisicoMutex.unlock();

    p.end();

}

