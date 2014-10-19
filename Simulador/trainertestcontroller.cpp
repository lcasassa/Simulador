#include "trainertestcontroller.h"
#include "robotquadrotor.h"
#include "objetocircunferencia.h"
#include "simulador.h"
#include "escenariotresobjetos.h"
#include "escenariounobjeto.h"
#include <QPointer>
#include <QFile>
#include <QTextStream>


TrainerTestController::TrainerTestController(Simulador *sim_, QObject *parent) :
    Trainer(sim_, parent), file("lala.txt")
{
}

void TrainerTestController::run() {

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

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

    doSimulation(f);
}

float TrainerTestController::doSimulation(fuzzy &b) {
    static int count = 0;
    float result=0;
    QTextStream out(&file);

    emit newFuzzy(b, true);

    EscenarioTresObjetos e(this);
    result = simulate(e, b, 40);

    EscenarioUnObjeto e2(this);
    result += simulate(e2, b, 60);

    out << result << " \n";
    qWarning("Results: %f count %d", result, count++);

    return result;
    //qWarning("loop trainer end.");
}

float TrainerTestController::simulate(Escenario &e, fuzzy &b, double time) {
    float result=0;

    //qWarning("loop trainer..");
    //msleep(100);
    //pause();
    //msleep(100);

    reset();

    e.registrarObjetos();

    QPointer<Fuzzyficacion> fuzzyficacion = new Fuzzyficacion();
    fuzzyficacion->setFuzzy(b);
    QPointer<ControlFuzzy> control = new ControlFuzzy(fuzzyficacion);
    QPointer<RobotQuadrotor> quad = new RobotQuadrotor(control);
    registrarObjeto(quad);

    play(time);
    if(sim != NULL && sim->odeRunning()) {

        //step(1000);
        //sleep(15);
        //    pause();
        result = quad->getMinDistance();
    }

    desregistrarObjeto(quad);

    e.desregistrarObjetos();

    while(sim == NULL || !sim->odeRunning());// {
        //msleep(1);
    //}

    return result;
}

