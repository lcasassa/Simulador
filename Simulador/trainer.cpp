#include "trainer.h"

Trainer::Trainer(QObject *parent) :
    QThread(parent)
{
}

Trainer::~Trainer() {

}

void Trainer::run() {

    qWarning("Trainer: Play");
    emit playOde();
    msleep(1000);
    qWarning("Trainer: Stop");
    emit stopOde();
    msleep(1000);
    qWarning("Trainer: Reset");
    emit resetOde();
    msleep(1000);
    qWarning("Trainer: Play");
    emit playOde();
    msleep(1000);

}
