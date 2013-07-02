#include "simulador.h"
#include <QPainter>
#include <QTimer>

Simulador::Simulador(QWidget *parent) :
    QWidget(parent)
{

    ode = new Ode(this);
//    QTimer::singleShot(100, this, SLOT(timeout()));

    timer = new QTimer();
    setRefrescoHz(30);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeout()));


}

Simulador::~Simulador() {
    stop();

    while(!listaObjetoFisico.isEmpty())
        delete listaObjetoFisico.takeFirst();

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
    listaObjetoFisico.append(objetoFisico);
}

bool Simulador::playPause() {
    if(timer->isActive())
        pause();
    else
        play();

    return timer->isActive();
}

void Simulador::play() {
    ode->playOde();
    timer->start();
}

void Simulador::pause() {
    ode->pauseOde();
    timer->stop();
}

void Simulador::stop() {
    timer->stop();
    ode->stopOde();
    ode->wait(3000);
    if(ode->isRunning()) {
        qWarning("Matando al thread");
    }
}

void Simulador::reset() {
    stop();

    while(!listaObjetoFisico.isEmpty())
        delete listaObjetoFisico.takeFirst();
    delete ode;

    ode = new Ode(this);
    QTimer::singleShot(100, this, SLOT(timeout()));

}

void Simulador::paintEvent(QPaintEvent *) {
    QPainter p;
    float radio;

    //if(!timer->isActive()) return;
    if(!ode->isRunning()) return;

    radio = (this->width()/this->height()) < 1 ? this->width() : this->height();

    p.begin(this);
    p.translate(radio/2,radio/2);
    p.scale(radio/10.0,radio/-10.0);

    for (int i = 0; i < listaObjetoFisico.size(); ++i) {
        listaObjetoFisico[i]->pintar(&p);
    }

    p.end();
}

