#include "trainer.h"

Trainer::Trainer(QObject *parent) :
    QThread(parent)
{
}

Trainer::~Trainer() {

}

void Trainer::run() {

    while(1) ;

}
