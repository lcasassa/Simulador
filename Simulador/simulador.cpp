#include "simulador.h"
#include <QPainter>
#include <QTimer>

Simulador::Simulador(QWidget *parent) :
    QWidget(parent)
{
    ode = new Ode(this);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(timeout()));
    timer->setInterval(1/0.1);
}

Simulador::~Simulador() {
    stop();
    delete ode;
    delete timer;
}

void Simulador::timeout() {
    this->repaint();
}

void Simulador::registrarObjeto(ObjetoFisico *objetoFisico) {
    listaObjetoFisico.append(objetoFisico);
}

bool Simulador::startStop() {
    if(timer->isActive())
        stop();
    else
        start();

    return timer->isActive();
}

void Simulador::start() {
    ode->start();
    timer->start();
}

void Simulador::stop() {
    timer->stop();
    ode->stopOde();
    ode->wait(3000);
    if(ode->isRunning()) {
        qWarning("Matando al thread");
    }
}

void Simulador::paintEvent(QPaintEvent *) {
    QPainter p;
    float radio;

    if(!timer->isActive()) return;

    radio = (this->width()/this->height()) < 1 ? this->width() : this->height();

    p.begin(this);
    p.translate(radio/2,radio/2);
    p.scale(radio/10.0,radio/-10.0);
//    p.scale(10000.0/(1000.0 * (this->height() < 600 ? this->height() : 600)), 10000.0/(1000.0 * (this->width() < 600 ? this->width() : 600)) * -1);
    for (int i = 0; i < listaObjetoFisico.size(); ++i) {
        listaObjetoFisico[i]->pintar(&p);
    }
//    p.drawText((this->width()-40)/2,x[2],255, 64, NULL, "Pelotita", NULL);
//    p.drawRect(QRectF(-4.7, -4.7, 9.4, 9.4));
    p.end();
}

