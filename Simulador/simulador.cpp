#include "simulador.h"
#include "traineralgoritmogenetico.h"
#include <QPainter>
#include <QTimer>
#include <QtGui/QApplication>

#include <QWaitCondition>
#include <QMutex>

class Sleep
{
public:
    static void msleep(unsigned long msecs)
    {
        QMutex mutex;
        mutex.lock();

        QWaitCondition waitCondition;
        waitCondition.wait(&mutex, msecs);

        mutex.unlock(); // Not necessary since new mutex will always be created,
                        // but since destroying locked mutex
                        // is bringing undefined behavior, let's follow some ethics
    }
};

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
    trainer = new TrainerAlgoritmoGenetico(this, this);

    connect(trainer, SIGNAL(playOde(double)),  this, SLOT(play(double)), Qt::BlockingQueuedConnection);
    connect(trainer, SIGNAL(stopOde()),  this, SLOT(stop()), Qt::BlockingQueuedConnection);
    connect(trainer, SIGNAL(delOde()),  this, SLOT(destroyOde()), Qt::BlockingQueuedConnection);
    connect(trainer, SIGNAL(resetOde()), this, SLOT(reset()), Qt::BlockingQueuedConnection);
    connect(trainer, SIGNAL(pauseOde()), this, SLOT(pause()), Qt::BlockingQueuedConnection);
    connect(trainer, SIGNAL(stepOde(int)), this, SLOT(step(int)), Qt::BlockingQueuedConnection);
    connect(trainer, SIGNAL(registrarObjetoSimulador(ObjetoFisico*)), this, SLOT(registrarObjeto(ObjetoFisico*)), Qt::BlockingQueuedConnection);
    connect(trainer, SIGNAL(desregistrarObjetoSimulador(ObjetoFisico*)), this, SLOT(desregistrarObjeto(ObjetoFisico*)), Qt::BlockingQueuedConnection);

    plotFuzzyInput = NULL;
    plotFuzzyOutput = NULL;
    qRegisterMetaType<fuzzy>( "fuzzy" );
    connect(trainer, SIGNAL(newFuzzy(fuzzy)), this, SLOT(newFuzzy(fuzzy)));
    connect(trainer, SIGNAL(bestFuzzy(fuzzy)), this, SLOT(bestFuzzy(fuzzy)));

}

void Simulador::setFuzzyWidgets(PlotFuzzy *plotFuzzyInput_, PlotFuzzy *plotFuzzyOutput_, PlotFuzzy *plotFuzzyInput2_, PlotFuzzy *plotFuzzyOutput2_) {
    plotFuzzyInput = plotFuzzyInput_;
    plotFuzzyOutput = plotFuzzyOutput_;
    plotFuzzyInput2 = plotFuzzyInput2_;
    plotFuzzyOutput2 = plotFuzzyOutput2_;
}

void Simulador::newFuzzy(fuzzy f) {
    if(plotFuzzyInput == NULL || plotFuzzyOutput == NULL)
        return;

    plotFuzzyInput->setDatos(0, f.input1[0][0], f.input1[0][0], f.input1[0][1]);
    plotFuzzyInput->setDatos(1, f.input1[1][0], (f.input1[1][0] + f.input1[1][1]) / 2, f.input1[1][1]);
    plotFuzzyInput->setDatos(2, f.input1[2][0], f.input1[2][1], f.input1[2][1]);
    plotFuzzyInput->repaint();

    plotFuzzyInput2->setDatos(0, f.input2[0][0], f.input2[0][0], f.input2[0][1], true);
    plotFuzzyInput2->setDatos(1, f.input2[1][0], (f.input2[1][0] + f.input2[1][1]) / 2, f.input2[1][1], true);
    plotFuzzyInput2->setDatos(2, f.input2[2][0], f.input2[2][1], f.input2[2][1], true);
    plotFuzzyInput2->repaint();

    return;
}

void Simulador::bestFuzzy(fuzzy f) {
    if(plotFuzzyInput == NULL || plotFuzzyOutput == NULL)
        return;

    plotFuzzyOutput->setDatos(0, f.input1[0][0], f.input1[0][0], f.input1[0][1]);
    plotFuzzyOutput->setDatos(1, f.input1[1][0], (f.input1[1][0] + f.input1[1][1]) / 2, f.input1[1][1]);
    plotFuzzyOutput->setDatos(2, f.input1[2][0], f.input1[2][1], f.input1[2][1]);
    plotFuzzyOutput->repaint();

    plotFuzzyOutput2->setDatos(0, f.input2[0][0], f.input2[0][0], f.input2[0][1], true);
    plotFuzzyOutput2->setDatos(1, f.input2[1][0], (f.input2[1][0] + f.input2[1][1]) / 2, f.input2[1][1], true);
    plotFuzzyOutput2->setDatos(2, f.input2[2][0], f.input2[2][1], f.input2[2][1], true);
    plotFuzzyOutput2->repaint();

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

void Simulador::registrarObjeto(ObjetoFisico *objetoFisico) {
    listaObjetoFisicoMutex.lock();
    listaObjetoFisico.append(objetoFisico);
    listaObjetoFisicoMutex.unlock();
}

void Simulador::desregistrarObjeto(ObjetoFisico *objetoFisico) {
    listaObjetoFisicoMutex.lock();
    objetoFisico->remove();
    listaObjetoFisico.removeOne(objetoFisico);
    listaObjetoFisicoMutex.unlock();
}

bool Simulador::playPause() {
    if(timer->isActive())
        pause();
    else
        play(1);

    return timer->isActive();
}

void Simulador::play(double sec) {
    timer->start();
    ode->playOde(sec);
    while(ode->getStatus() > Ode::PAUSE)
        QApplication::processEvents();
    //if(sendCommandDone)
    //    emit commandDone();
}

void Simulador::step(int steps_) {
    timer->stop();
    ode->stepOde(steps_);
    //while(ode->getStatus() != Ode::PAUSE) ;
    //for(int i=0; i<10; i++)
    //    QTimer::singleShot(100*i, this, SLOT(timeout())); // just in case ode takes more time to solve all the steps
}

void Simulador::pause() {
    ode->pauseOde();
    timer->stop();
}

void Simulador::stop() {
    timer->stop();
    ode->stopOde();

    //int i=0;
    //while(ode->getStatus() >= Ode::STOP && i++<=10) {
    //    Sleep::msleep(10);
    //}
    //if(sendCommandDone) {
    //    i=0;
    //    while(trainer->isRunning() && i++<=10) {
    //        Sleep::msleep(10);
    //    }
    //}

}

void Simulador::destroyOde() {
    ode->finish();
    ode->wait(100);

    if(ode->isRunning()) {
        qWarning("Matando al thread");
        ode->terminate();
    }
}

bool Simulador::odeRunning() {

    int i = ode->getStatus();

    return i >= 0;
}

void Simulador::reset() {
    stop();

    listaObjetoFisicoMutex.lock();
    listaObjetoFisico.clear();
    listaObjetoFisicoMutex.unlock();

    destroyOde();
    delete ode;

    ode = new Ode(this, this);

    QTimer::singleShot(100, this, SLOT(timeout()));

    while(!ode->isPaused()) ;

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


