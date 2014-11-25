#include "traineralgoritmogenetico.h"
#include "robotquadrotor.h"
#include "objetocircunferencia.h"
#include "simulador.h"
#include "escenariotresobjetos.h"
#include "escenariotresobjetoscerca.h"
#include "escenariounobjeto.h"
#include "escenariotest.h"
#include <QPointer>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>
#include <QApplication>

#include "ui_mainwindow.h"
#include "mainwindow.h"

#include "simgalib/simgalib.h"
#include "simgalib/simpsolib.h"
#include "simgalib/simtstlib.h"

//#define ONE_LONG_RUN
//#define FIVE_SHORT_RUN
//#define ONE_SHORT_RUN
//#define SHORT_TEST_RUN

//#define SIMULATE_ESCENARIO_TRES_OBJETOS
//#define SIMULATE_ESCENARIO_TRES_OBJETOS_CERCA
//#define SIMULATE_ESCENARIO_UNO_OBJETO
#define SIMULATE_ESCENARIO_MUCHOS_ESCENARIOS

#define TEST_TUNING
//#define MANUAL_TUNING
//#define AUTO_TUNING


using namespace simgalib;
using namespace simpsolib;
using namespace simtstlib;


TrainerAlgoritmoGenetico *trainer = NULL;

TrainerAlgoritmoGenetico::TrainerAlgoritmoGenetico(Simulador *sim_, QObject *parent) :
    Trainer(sim_, parent)
{
    trainer = this;
    best_result = 0;
}

double quad_test_fn_real(int num_vars, double x[])
{
    double rslt=0.0;
    fuzzy f;
    int k=0;
    f.input1[0][0] = x[k++];
    f.input1[0][1] = x[k++];
    f.input1[1][0] = x[k++];
    f.input1[1][1] = x[k++];
    f.input1[2][0] = x[k++];
    f.input1[2][1] = x[k++];

    f.input2[0][0] = x[k++];
    f.input2[0][1] = x[k++];
    f.input2[1][0] = x[k++];
    f.input2[1][1] = x[k++];
    f.input2[2][0] = x[k++];
    f.input2[2][1] = x[k++];

/*
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
*/

    f.output[0][0] = -2.00;
    f.output[0][1] =  0.00;
    f.output[1][0] = -1.00;
    f.output[1][1] =  0.00;
    f.output[2][0] = -0.50;
    f.output[2][1] =  0.50;
    f.output[3][0] =  0.00;
    f.output[3][1] =  1.00;

    rslt = (double)trainer->doSimulation(f);
    return rslt;
}

double quad_test_fn(int num_vars, int bits_per_var, vector<double> range_low, vector<double> range_high, std::vector<int> genes)
{
    unsigned int uint_genes;
    int one_to_shift;
    vector<double> a_range=range_low;
    vector<double> b_range=range_high;
    double result=0;
    double x[num_vars];
    //int num_genes=genes.size();

    for(int k=0; k<num_vars; k++) {
        x[k]=0.0;
        uint_genes=0;
        one_to_shift=1;
        for (int i=0;i<bits_per_var;i++)
        {
            uint_genes += (genes[(k*bits_per_var)+i] * one_to_shift );
            one_to_shift=one_to_shift<<1;
        }

        // Convert the unsigned integer sum of the genes into floating point number x1
        x[k] = a_range[k] + (uint_genes * ((b_range[k]-a_range[k])/(pow((double) 2.0, QUAD_FN_BITS_PER_VAR)-1)));

    }


    result=quad_test_fn_real((int)num_vars, &x[0]);

    return result;
}

void TrainerAlgoritmoGenetico::run() {

#ifdef TEST_TUNING

    QStringList argumentList(QCoreApplication::arguments());


    Ui::MainWindow *ui = sim->getUI();
    ui->spinBoxLoopSleepUs->setValue(0);
    (qobject_cast<MainWindow*>(sim->parent()->parent()->parent()))->setWindowTitle("Fuzzy " + argumentList[1]);

    file.setFileName("outputTest.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    int run = 2000;
    while( run-- > 0) {
        fuzzy f;
        Fuzzyficacion::importFuzzy(f, argumentList[1]);

        doSimulation(f, false);
    }

#endif

#ifdef MANUAL_TUNING

    file.setFileName("outputManual.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    int run = 2000;
    while( run-- > 0) {
        fuzzy f;
        Ui::MainWindow *ui = sim->getUI();
        f.input1[0][0] = ui->doubleSpinBox00->value();
        f.input1[0][1] = ui->doubleSpinBox01->value();
        f.input1[1][0] = ui->doubleSpinBox10->value();
        f.input1[1][1] = ui->doubleSpinBox11->value();
        f.input1[2][0] = ui->doubleSpinBox20->value();
        f.input1[2][1] = ui->doubleSpinBox21->value();

        f.input2[0][0] = ui->doubleSpinBox30->value();
        f.input2[0][1] = ui->doubleSpinBox31->value();
        f.input2[1][0] = ui->doubleSpinBox40->value();
        f.input2[1][1] = ui->doubleSpinBox41->value();
        f.input2[2][0] = ui->doubleSpinBox50->value();
        f.input2[2][1] = ui->doubleSpinBox51->value();

        f.output[0][0] = -2.00;
        f.output[0][1] =  0.00;
        f.output[1][0] = -1.00;
        f.output[1][1] =  0.00;
        f.output[2][0] = -0.50;
        f.output[2][1] =  0.50;
        f.output[3][0] =  0.00;
        f.output[3][1] =  1.00;

        doSimulation(f, false);
    }

#endif

#ifdef AUTO_TUNING

    QStringList argumentList(QCoreApplication::arguments());
    //msleep(100);
    //reset();

    //QByteArray b;
    //b = Fuzzyficacion::serialize(f);

    if(argumentList.size() != 5)
        qWarning("Bad arguments!");

    outputFileName = argumentList[1];
    QString trainerAlgorithm = argumentList[2].toLower();
    int popNumber = argumentList[3].toInt();
    // 4 is density of the mass

    (qobject_cast<MainWindow*>(sim->parent()->parent()->parent()))->setWindowTitle("Algoritmo " + trainerAlgorithm);

    qWarning() << "outputFileName: " << outputFileName << " trainerAlgorithm: " <<  trainerAlgorithm << " popNumber: " << popNumber;

    file.setFileName(outputFileName + ".txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

#ifdef ONE_LONG_RUN
    int number_runs=1;
    //ga parms
    int ga_pop=15;
    int ga_iters=10;
    //sh & sa parms
    int sh_sa_iters=ga_pop*ga_iters;
    int sh_sa_starts=1;
    //pso parms
    int pso_pop=50;
    int pso_iters=100;
    float phi_p=1.49445;
    float phi_g=1.49445;
    float omega=.729;

#else
#ifdef ONE_SHORT_RUN
    int number_runs=5;
    //ga parms
    int ga_pop=5;
    int ga_iters=10;
    //sh & sa parms
    int sh_sa_iters=ga_pop*ga_iters;
    int sh_sa_starts=5;
    //pso parms
    int pso_pop=5;
    int pso_iters=10;
    float phi_p=1.49445;
    float phi_g=1.49445;
    float omega=.729;
#else
#ifdef FIVE_SHORT_RUN
    int number_runs=5;
    //ga parms
    int ga_pop=5;
    int ga_iters=10;
    //sh & sa parms
    int sh_sa_iters=ga_pop*ga_iters;
    int sh_sa_starts=5;
    //pso parms
    int pso_pop=5;
    int pso_iters=10;
    float phi_p=1.49445;
    float phi_g=1.49445;
    float omega=.729;
#else
#ifdef SHORT_TEST_RUN
    int number_runs=1;
    //ga parms
    int ga_pop=15;
    int ga_iters=4;
    //sh & sa parms
    int sh_sa_iters=ga_pop*ga_iters;
    int sh_sa_starts=5;
    //pso parms
    int pso_pop=20;
    int pso_iters=100;
    float phi_p=1.49445;
    float phi_g=1.49445;
    float omega=.729;
#else
    int number_runs=10;
    //ga parms
    int ga_pop=20;
    int ga_iters=100;
    //sh & sa parms
    int sh_sa_iters=ga_pop*ga_iters;
    int sh_sa_starts=5;
    //pso parms
    int pso_pop=20;
    int pso_iters=100;
    float phi_p=1.49445;
    float phi_g=1.49445;
    float omega=.729;
#endif
#endif
#endif
#endif

    ga_iters = ga_pop*ga_iters/popNumber;
    ga_pop = popNumber;
    pso_pop = ga_pop;
    pso_iters = ga_iters;
    sh_sa_iters=ga_pop*ga_iters;

    qWarning() << "ga_iters: " << ga_iters << " ga_pop: " <<  ga_pop;
    // simgalib::EvalFN eval_fn((char *)"DEJONG1", DEJONG1_FN_NUM_VARS,DEJONG1_FN_BITS_PER_VAR,DEJONG1_FN_LOWER_RANGE, DEJONG1_FN_UPPER_RANGE, dejong1_test_fn);

    // perform PSO experiment
    std::vector<double> lower_range(QUAD_FN_NUM_VARS);
    std::vector<double> upper_range(QUAD_FN_NUM_VARS);

    for (int i=0; i< QUAD_FN_NUM_VARS; i++)
    {
        if(i >= QUAD_FN_NUM_VARS/2) {
            lower_range[i]=QUAD_FN_LOWER_RANGE_2;
            upper_range[i]=QUAD_FN_UPPER_RANGE_2;
        } else {
            lower_range[i]=QUAD_FN_LOWER_RANGE_1;
            upper_range[i]=QUAD_FN_UPPER_RANGE_1;
        }
    }

    if(trainerAlgorithm == "pso") {
        simpsolib::EvalFN pso_eval_fn((char *)"QUAD", QUAD_FN_NUM_VARS, lower_range, upper_range, quad_test_fn_real);
        run_pso(pso_eval_fn, number_runs, pso_pop, pso_iters, phi_p, phi_g, omega);
    } else if(trainerAlgorithm == "ga") {
        simgalib::EvalFN eval_fn((char *)"QUAD", QUAD_FN_NUM_VARS, QUAD_FN_BITS_PER_VAR, lower_range, upper_range, quad_test_fn);
        run_ga(eval_fn, number_runs, ga_pop, ga_iters, simgalib::Tournament, true, 0.5, 0.001, 0.75, 1.1);
    } else if(trainerAlgorithm == "sh") {
        simgalib::EvalFN eval_fn((char *)"QUAD", QUAD_FN_NUM_VARS, QUAD_FN_BITS_PER_VAR, lower_range, upper_range, quad_test_fn);
        run_sh(eval_fn, number_runs, sh_sa_iters, sh_sa_starts);
    } else if(trainerAlgorithm == "sa") {
        simgalib::EvalFN eval_fn((char *)"QUAD", QUAD_FN_NUM_VARS, QUAD_FN_BITS_PER_VAR, lower_range, upper_range, quad_test_fn);
        run_sa(eval_fn, number_runs, sh_sa_iters, sh_sa_starts, 1, 0.01);
    }
#endif

    // Save fuzzy
    //Fuzzyficacion::exportFuzzy(best_fuzzy, outputFileName + "_fuzzy.txt");

    QApplication::exit(0);

}

float TrainerAlgoritmoGenetico::doSimulation(fuzzy &b, bool setSpinBox) {
    static int count = 0;
    float result=0;
    float result_tmp=0;
#ifdef TEST_TUNING;
    int moreTime = 100;
#else
    int moreTime = 0;
#endif
    QTextStream out(&file);

    emit newFuzzy(b, setSpinBox);

#ifdef SIMULATE_ESCENARIO_TRES_OBJETOS
    EscenarioTresObjetos e(this);
    result += simulate(e, b, 40 + moreTime);
#endif

#ifdef SIMULATE_ESCENARIO_TRES_OBJETOS_CERCA
    EscenarioTresObjetosCerca e2(this);
    result_tmp = simulate(e2, b, 90 + moreTime);
    result_tmp *= 3;
    result += result_tmp;
#endif

#ifdef SIMULATE_ESCENARIO_UNO_OBJETO
    EscenarioUnObjeto e3(this);
    result += simulate(e3, b, 60 + moreTime);
#endif

#ifdef SIMULATE_ESCENARIO_MUCHOS_ESCENARIOS
    EscenarioTest e4(this);
    result_tmp = simulate(e4, b, 60 + moreTime);
    if(result_tmp == 0)
        qWarning("Choque EscenarioTest");
    result += result_tmp;
    EscenarioTest5 e8(this);
    result_tmp = simulate(e8, b, 60 + moreTime);
    if(result_tmp == 0)
        qWarning("Choque EscenarioTest5");
    result += result_tmp;
    EscenarioTest4 e7(this);
    result_tmp = simulate(e7, b, 60 + moreTime);
    if(result_tmp == 0)
        qWarning("Choque EscenarioTest4");
    result += result_tmp;
    EscenarioTest3 e6(this);
    result_tmp = simulate(e6, b, 60 + moreTime);
    if(result_tmp == 0)
        qWarning("Choque EscenarioTest3");
    result += result_tmp;
    EscenarioTest2 e5(this);
    result_tmp = simulate(e5, b, 60 + moreTime);
    if(result_tmp == 0)
        qWarning("Choque EscenarioTest2");
    result += result_tmp;
#endif

    if(result > best_result) {
        best_result = result;
        best_fuzzy = b;
        emit bestFuzzy(b);
        Fuzzyficacion::exportFuzzy(best_fuzzy, outputFileName + "_fuzzy.txt");
    }
    out << result << " " << best_result << "\n";
//#ifdef PRINT_RESULT
    qWarning("Results: %f count %d", result, count++);
//#endif

    return result;
    //qWarning("loop trainer end.");
}

float TrainerAlgoritmoGenetico::simulate(Escenario &e, fuzzy &b, double time) {
    double result=0;

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

        // alfa = 0.5 == muy dominante la aceleracion

        double alfa = 0.5;
        double beta = 0.25; // beta = 1 -> maxg inaceptable, beta = 0 -> sumg inaceptable

        double maxg = quad->getMaxG()*(beta);
        double sumg = quad->getSumG()*(1.0-beta);
        //qWarning("maxg %f sumg %f", maxg, sumg);

        result = (sumg + maxg);
        //result = ;


        result = 1 / (result);

        result *= alfa;

        result += quad->getMinDistance() * (1.0-alfa);
        int crash = quad->crashCount();
        double mindist = quad->getMinDistance();
        if(crash > 0 || 0.001 >= mindist)
            result = 0;
        //result = quad->getMinDistance();
        //qWarning("%f %f -> %f", quad->getMaxG(), quad->getMinDistance(), result);
    }

    desregistrarObjeto(quad);

    e.desregistrarObjetos();

    while(sim == NULL || !sim->odeRunning());// {
        //msleep(1);
    //}

    return result;
}
