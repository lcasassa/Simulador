/*
 * FILE: simpsolib.h, v.1.6.0, 3/18/2011
 * Author: Tomas V. Arredondo
 *
 * SimGALib: A simple yet flexible PSO implementation in C++.
 *
 * DISCLAIMER: No liability is assumed by the author for any use made
 * of this program.
 * DISTRIBUTION: Any use may be made of this program, as long as the
 * clear acknowledgment is made to the author in code and runtime executables
 */
#ifndef SIMPSOLIB_H
#define SIMPSOLIB_H

#include <iostream>
#include <vector>
#include <cmath>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simtstlib.h"

namespace simpsolib
{
    using namespace std;

    // Early declaration
    class EvalFN;

    // Currently implemented optimization methods:
    // Particle Swarm Optimization (Kennedy and Eberhart 1995)
    // there are simplified versions where phy_g=0, omega=0 (Simplifying PSO, Pedersen 2009)
    int run_pso(EvalFN eval, int number_runs, int pso_pop_size, int pso_number_iters,
                float phi_p, float phi_g, float omega);

// **********************************
// Default simulation values here
#define POPULATION_SIZE 100
#define NUM_DIMS_UNDEF -1
#define NUM_ITERATIONS 100
// Default simulation values here
// **********************************

    class Organism
    {
    public:
        Organism()
        {
            num_dims=NUM_DIMS_UNDEF;
            best_value=0.0;
            value=0.0;
            cout << "Error: Called Organism constructor without parameters\n" << endl;
        }

        Organism(int tmp_num_dims)
        {
            num_dims=tmp_num_dims;
            position = vector<double>(num_dims);
            velocity = vector<double>(num_dims);
            best_position = vector<double>(num_dims);
            best_value=0.0;
            value=0.0;
        }
        friend ostream & operator<<(ostream& output, const Organism& p);
        friend class Population;
        vector<double> position;
        vector<double> velocity;
        double value;
        vector<double> best_position;
        double best_value;
        int num_dims;           // Number of dimensions in optimization
    };
    /*
        // organism sorting comparison functor: greater to lesser order
        struct greater_mag : public binary_function<Organism *, Organism *, bool>
        {
            bool operator()(Organism *x, Organism *y)
            {
                return x->fitness > y->fitness;
            }
        };
    */
    // Early declaration
    class Population_data;

    class EvalFN
    {
        friend class Population;
    public:
        int num_parms;
        vector<double> lower_range;
        vector<double> upper_range;
        double (*eval_fn)(int, double []);
        char szName[256];
        EvalFN(): num_parms(0), eval_fn(0)
        {
            ;
        }
        EvalFN(char *tmp_name, int tmp_num_parms, vector<double> tmp_lower_range, vector<double> tmp_upper_range, double (*tmp_eval_fn)(int, double []))
        {
            strcpy(szName, tmp_name);
            num_parms=tmp_num_parms;

            lower_range=vector<double> (num_parms);
            upper_range=vector<double> (num_parms);

            lower_range=tmp_lower_range;
            upper_range=tmp_upper_range;
            /*
            for (int i=0; i< tmp_num_dims; i++)
            {
                lower_range[i]=tmp_lower_range[i];
                upper_range[i]=tmp_upper_range[i];
            }
            */
            eval_fn=tmp_eval_fn;
        }
        double evaluate(vector<double> position);
    };

    class Population
    {
    private:
        int population_size;
        int num_iterations;
        EvalFN evaluator;
        vector<double> overall_best_position;
        double overall_best_value;
        int num_dims;
        float phi_p;
        float phi_g;
        float omega;
        bool rand_particle_upd_flag;

    public:
        vector<Organism *> pool;
        void create();
        void destroy();
        void display();
        void evaluate();
        void update_vel(/*const Population_data& pop_info*/);
        void update_pos(/*const Population_data& pop_info*/);

        Population()
        {
            population_size=POPULATION_SIZE;
            num_iterations=NUM_ITERATIONS;
            num_dims=NUM_DIMS_UNDEF;
            overall_best_value=0.0;
        }
        Population(int tmp_num_dims)
        {
            // This population constructor is passed the number of genes per Organism
            population_size=POPULATION_SIZE;
            num_iterations=NUM_ITERATIONS;
            num_dims=tmp_num_dims;
            overall_best_value=0.0;
        }
        ~Population()
        {
            ;
        }
        void setEvalFN(EvalFN tmp_evaluator)
        {
            evaluator=tmp_evaluator;
        }
        void setNumIters(int tmp_numiters)
        {
            num_iterations=tmp_numiters;
        }
        int getNumIters() const
        {
            return num_iterations;
        }
        void setSize(int tmp_size)
        {
            population_size=tmp_size;
        }
        int getSize() const
        {
            return population_size;
        }
        int getNumDims() const
        {
            return num_dims;
        }
        float getPhiG() const
        {
            return phi_g;
        }
        void setPhiG(float tmp_phi_g)
        {
            phi_g=tmp_phi_g;
        }
        float getPhiP() const
        {
            return phi_p;
        }
        void setPhiP(float tmp_phi_p)
        {
            phi_p=tmp_phi_p;
        }
        float getOmega() const
        {
            return omega;
        }
        void setOmega(float tmp_omega)
        {
            omega=tmp_omega;
        }
        bool getRandPartUpdFlag() const
        {
            return rand_particle_upd_flag;
        }
        void setRandPartUpdFlag(bool tmp_rand_particle_upd_flag)
        {
            rand_particle_upd_flag=tmp_rand_particle_upd_flag;
        }

    };

    class Population_data
    {
    public:
        int           max_index;
        //Organism      max_organism;
        double        max_value;
        int           min_index;
        //Organism      min_organism;
        double        min_value;
        double        avg_value;
        double        sum_values;

        void clear_pop_data()
        {
            max_index=0;
            max_value=0;
            min_index=0;
            min_value=0;
            avg_value=0;
            sum_values=0;
        }
        void evaluate_population_info(Population * pop);
        void display_population_stats();
    };




} // namespace simpsolib


#endif // SIMPSOLIB_H
