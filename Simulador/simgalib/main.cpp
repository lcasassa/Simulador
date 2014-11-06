/*
 * FILE: main.cpp, v.1.6.0, 3/18/2011
 * Author: Tomas V. Arredondo
 *
 * Example of a C++ application using SimGALib and SimPSOLib.
 *
 * This is NOT a tutorial on GA as there are many tutorials and books on this
 * subject see http://en.wikipedia.org/wiki/Genetic_algorithm for more information.
 *
 * To change the function and range being optimized go to ga.h and change
 * FUNCTION_LOWER_RANGE, FUNCTION_UPPER_RANGE and FUNCTION definitions.
 *
 * DISCLAIMER: No liability is assumed by the author for any use made
 * of this program.
 * DISTRIBUTION: Any use may be made of this program, as long as the
 * clear acknowledgment is made to the author in code and runtime executables
 */
#include <iostream>
#include <ctime>
#include <cmath>
#include <queue>
#include "simgalib.h"
#include "simpsolib.h"
#include "simtstlib.h"

using namespace simgalib;
using namespace simpsolib;
using namespace simtstlib;

int main()
{
    int number_runs=50;
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

    // simgalib::EvalFN eval_fn((char *)"DEJONG1", DEJONG1_FN_NUM_VARS,DEJONG1_FN_BITS_PER_VAR,DEJONG1_FN_LOWER_RANGE, DEJONG1_FN_UPPER_RANGE, dejong1_test_fn);
    simgalib::EvalFN eval_fn((char *)"QUATTRO", QUATRO_FN_NUM_VARS,QUATRO_FN_BITS_PER_VAR,QUATR_FN_LOWER_RANGE, QUATRO_FN_UPPER_RANGE, quattro_test_fn);

    // perform GA experiment
    run_ga(eval_fn, number_runs, ga_pop, ga_iters,Tournament,true,0.5,0.001,0.75,1.1);

    // perform stochastic hillclimbing experiment
    // for same number fn evals use sh_iters = ga_pop_size*ga_number_iters
    run_sh(eval_fn, number_runs, sh_sa_iters, sh_sa_starts);

    // perform simulated annealing experiment
    // for same number fn evals use sh_iters = ga_pop_size*ga_number_iters
    run_sa(eval_fn, number_runs, sh_sa_iters, sh_sa_starts, 50, 10);

    // perform PSO experiment
    vector<double> lower_range(QUATRO_FN_NUM_VARS);
    vector<double> upper_range(QUATRO_FN_NUM_VARS);

    for (int i=0; i< QUATRO_FN_NUM_VARS; i++)
    {
        lower_range[i]=QUATRO_FN_LOWER_RANGE;
        upper_range[i]=QUATRO_FN_UPPER_RANGE;
    }

    simpsolib::EvalFN pso_eval_fn((char *)"DEJONG2", DEJONG2_FN_NUM_VARS,lower_range, upper_range, dejong2_test_fn_real);
    run_pso(pso_eval_fn, number_runs, pso_pop, pso_iters, phi_p, phi_g, omega);
}
