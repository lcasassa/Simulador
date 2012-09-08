#include "simulador.h"
#include <QPainter>
#include <QTimer>

Simulador::Simulador(QWidget *parent) :
    QWidget(parent)
{
    ode = new Ode(this);
    ode->start();

    QTimer *q;
    q = new QTimer();
    connect(q, SIGNAL(timeout()),this, SLOT(timeout()));
    q->start(20);
}

void Simulador::timeout() {
    this->repaint();
}

void Simulador::registrarObjeto(ObjetoFisico *objetoFisico) {
    listaObjetoFisico.append(objetoFisico);
}

void Simulador::paintEvent(QPaintEvent *) {
    QPainter p;

    p.begin(this);
    for (int i = 0; i < listaObjetoFisico.size(); ++i) {
        listaObjetoFisico[i]->pintar(p);
    }
//    p.drawText((this->width()-40)/2,x[2],255, 64, NULL, "Pelotita", NULL);
    p.drawRect(0,0,this->width()-1,this->height()-1);
    p.end();
}

