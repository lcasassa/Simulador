#include "traineralgoritmogenetico.h"
#include "robotquadrotor.h"
#include "objetocircunferencia.h"
#include <QPointer>

TrainerAlgoritmoGenetico::TrainerAlgoritmoGenetico(QObject *parent) :
    Trainer(parent)
{
}

void TrainerAlgoritmoGenetico::run() {
    //msleep(100);
    //reset();
    int run = 2;
    while( run-- > 0) {
        qWarning("loop trainer..");
        //msleep(100);
        //pause();
        //msleep(100);
        QPointer<ObjetoCircunferencia> objetoCircunferencia[3];
        objetoCircunferencia[0] = new ObjetoCircunferencia(0.5,1,0.3, 0, 2);
        objetoCircunferencia[1] = new ObjetoCircunferencia(0.5,1,0.3, 2, 0);
        objetoCircunferencia[2] = new ObjetoCircunferencia(0.5,1,0.3, 0,-2);
        for(int i=0; i<3; i++)
            registrarObjeto( objetoCircunferencia[i] );

        for(int k=0;k<2;k++) {
            QPointer<Fuzzyficacion> fuzzyficacion = new Fuzzyficacion();
            QPointer<ControlFuzzy> control = new ControlFuzzy(fuzzyficacion);
            QPointer<RobotQuadrotor> quad = new RobotQuadrotor(control);


            registrarObjeto(quad);


            play();
            //step(1000);
            sleep(15);
            //    pause();
            qWarning("Results: %f", quad->getMinDistance());

            desregistrarObjeto(quad);
        }

        for(int i=0; i<3; i++)
            desregistrarObjeto( objetoCircunferencia[i] );

        qWarning("loop trainer end.");

    }
}

