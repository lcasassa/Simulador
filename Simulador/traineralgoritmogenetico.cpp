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
        //qWarning("loop trainer..");
        //msleep(100);
        //pause();
        //msleep(100);

        reset();

        QPointer<ObjetoCircunferencia> objetoCircunferencia[3];
        objetoCircunferencia[0] = new ObjetoCircunferencia(0.5,1,0.3, 0, 2);
        objetoCircunferencia[1] = new ObjetoCircunferencia(0.5,1,0.3, 2, 0);
        objetoCircunferencia[2] = new ObjetoCircunferencia(0.5,1,0.3, 0,-2);
        for(int i=0; i<3; i++)
            registrarObjeto( objetoCircunferencia[i] );


        fuzzy f;
        f.input1[0][0] = 0.00;
        f.input1[0][1] = 0.50;
        f.input1[1][0] = 0.25;
        f.input1[1][1] = 0.75;
        f.input1[2][0] = 0.50;
        f.input1[2][1] = 1.00;

        f.input2[0][0] = -1.00;
        f.input2[0][1] = -0.25;
        f.input2[1][0] = -0.50;
        f.input2[1][1] =  0.50;
        f.input2[2][0] =  0.25;
        f.input2[2][1] =  1.00;

        f.output[0][0] = -2.00;
        f.output[0][1] =  0.00;
        f.output[1][0] = -1.00;
        f.output[1][1] =  0.00;
        f.output[2][0] = -0.50;
        f.output[2][1] =  0.50;
        f.output[3][0] =  0.00;
        f.output[3][1] =  1.00;

        QByteArray b;
        b = Fuzzyficacion::serialize(f);

        for(int k=0;k<1;k++) {
            QPointer<Fuzzyficacion> fuzzyficacion = new Fuzzyficacion();
            fuzzyficacion->setFuzzy(b);
            QPointer<ControlFuzzy> control = new ControlFuzzy(fuzzyficacion);
            QPointer<RobotQuadrotor> quad = new RobotQuadrotor(control);
            registrarObjeto(quad);

            play(60);
            //step(1000);
            //sleep(15);
            //    pause();
            qWarning("Results: min: %f prom: %f", quad->getMinDistance(), quad->getPromDistance());

            desregistrarObjeto(quad);

        }

        for(int i=0; i<3; i++)
            desregistrarObjeto( objetoCircunferencia[i] );

        //qWarning("loop trainer end.");

    }
}

