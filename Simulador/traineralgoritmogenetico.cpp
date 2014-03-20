#include "traineralgoritmogenetico.h"
#include "robotquadrotor.h"
#include "objetocircunferencia.h"
#include "simulador.h"
#include <QPointer>

#include "simgalib/simgalib.h"
#include "simgalib/simpsolib.h"
#include "simgalib/simtstlib.h"

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

double quad_test_fn(int num_vars, int bits_per_var, double range_low_1, double range_high_1, double range_low_2, double range_high_2, std::vector<int> genes)
{
    /*
    unsigned int uint_genes;
    int one_to_shift;
    double a_range_1=range_low_1;
    double b_range_1=range_high_1;
    double a_range_2=range_low_2;
    double b_range_2=range_high_2;
    double result=0;
    double x[num_vars];
    int num_genes=genes.size();

    for(int k=0; k<num_vars; k++) {
        x[k]=0.0;
        uint_genes=0;
        one_to_shift=1;
        for (int i=0;i<num_genes;i++)
        {
            uint_genes += (genes[(k*bits_per_var)+i] * one_to_shift );
            one_to_shift=one_to_shift<<1;
        }

        // Convert the unsigned integer sum of the genes into floating point number x1
        if(k < (num_vars/2)) {
            x[k] = a_range_1 + (uint_genes * ((b_range_1-a_range_1)/(pow((double) 2.0, num_genes)-1)));
        } else {
            x[k] = a_range_2 + (uint_genes * ((b_range_2-a_range_2)/(pow((double) 2.0, num_genes)-1)));
        }

    }


    result=quad_test_fn_real((int)num_vars, &x[0]);

    return result;
*/
    return 0.0;
}

void TrainerAlgoritmoGenetico::run() {
    //msleep(100);
    //reset();

    //QByteArray b;
    //b = Fuzzyficacion::serialize(f);


    int number_runs=50;
    //ga parms
    //int ga_pop=20;
    //int ga_iters=100;
    //sh & sa parms
    //int sh_sa_iters=ga_pop*ga_iters;
    //int sh_sa_starts=5;
    //pso parms
    int pso_pop=20;
    int pso_iters=100;
    float phi_p=1.49445;
    float phi_g=1.49445;
    float omega=.729;

    // simgalib::EvalFN eval_fn((char *)"DEJONG1", DEJONG1_FN_NUM_VARS,DEJONG1_FN_BITS_PER_VAR,DEJONG1_FN_LOWER_RANGE, DEJONG1_FN_UPPER_RANGE, dejong1_test_fn);
    //simgalib::EvalFN eval_fn((char *)"QUAD", QUAD_FN_NUM_VARS, QUAD_FN_BITS_PER_VAR, QUAD_FN_LOWER_RANGE, QUAD_FN_UPPER_RANGE, quad_test_fn);

    // perform PSO experiment
    std::vector<double> lower_range(QUAD_FN_NUM_VARS);
    std::vector<double> upper_range(QUAD_FN_NUM_VARS);

    for (int i=0; i< QUAD_FN_NUM_VARS; i++)
    {
        if(i > QUAD_FN_NUM_VARS/2) {
            lower_range[i]=QUAD_FN_LOWER_RANGE_2;
            upper_range[i]=QUAD_FN_UPPER_RANGE_2;
        } else {
            lower_range[i]=QUAD_FN_LOWER_RANGE_1;
            upper_range[i]=QUAD_FN_UPPER_RANGE_1;
        }
    }
    simpsolib::EvalFN pso_eval_fn((char *)"QUAD", QUAD_FN_NUM_VARS, lower_range, upper_range, quad_test_fn_real);
    run_pso(pso_eval_fn, number_runs, pso_pop, pso_iters, phi_p, phi_g, omega);

    /*int run = 2;
    while( run-- > 0) {
        b = b+1;
        doSimulation(b);
    }*/

/*
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
*/
}

float TrainerAlgoritmoGenetico::doSimulation(fuzzy &b) {
    static int count = 0;
    float result=0;
    emit newFuzzy(b);
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



    //for(int k=0;k<1;k++) {
        QPointer<Fuzzyficacion> fuzzyficacion = new Fuzzyficacion();
        fuzzyficacion->setFuzzy(b);
        QPointer<ControlFuzzy> control = new ControlFuzzy(fuzzyficacion);
        QPointer<RobotQuadrotor> quad = new RobotQuadrotor(control);
        registrarObjeto(quad);

        play(40);
        if(sim != NULL && sim->odeRunning()) {

            //step(1000);
            //sleep(15);
            //    pause();
            qWarning("Results: min: %f prom: %f count %d", quad->getMinDistance(), quad->getPromDistance(), count++);

            result = quad->getMinDistance();
            if(result > best_result) {
                best_result = result;
                best_fuzzy = b;
                emit bestFuzzy(b);
            }
        }

        desregistrarObjeto(quad);

    //}

    for(int i=0; i<3; i++)
        desregistrarObjeto( objetoCircunferencia[i] );

    while(sim == NULL || !sim->odeRunning()) {
        msleep(100);
    }

    return result;
    //qWarning("loop trainer end.");
}
