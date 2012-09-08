#include "simulador.h"
#include <QPainter>
#include <QTimer>

Simulador::Simulador(QWidget *parent) :
    QWidget(parent)
{
    ode = new Ode(this);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(timeout()));
    timer->setInterval(20);
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

    if(!timer->isActive()) return;

    p.begin(this);
    p.translate(this->width()/2,this->height()/2);
    p.scale(this->width()/10.0,this->height()/-10.0);
//    p.scale(10000.0/(1000.0 * (this->height() < 600 ? this->height() : 600)), 10000.0/(1000.0 * (this->width() < 600 ? this->width() : 600)) * -1);
    for (int i = 0; i < listaObjetoFisico.size(); ++i) {
        listaObjetoFisico[i]->pintar(&p);
    }
//    p.drawText((this->width()-40)/2,x[2],255, 64, NULL, "Pelotita", NULL);
//    p.drawRect(QRectF(-4.7, -4.7, 9.4, 9.4));
    p.end();
}

