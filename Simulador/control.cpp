#include "control.h"

Control::Control(QWidget *parent) :
    QWidget(parent)
{
}

Control::~Control() {

}

void Control::loopControl(qreal *distanciaDetectado, qreal *salidas) {

}

void Control::paintEvent(QPaintEvent *) {
    QPainter p;
//    float radio;

//    radio = (this->width()/this->height()) < 1 ? this->width() : this->height();

    p.begin(this);
    p.scale(40,-40);
    p.translate(0, -4);

    pintar(&p);
    p.end();
}

void Control::pintar(QPainter *p) {

}
