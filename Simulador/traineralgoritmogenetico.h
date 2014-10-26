#ifndef TRAINERALGORITMOGENETICO_H
#define TRAINERALGORITMOGENETICO_H

#include "trainer.h"
//#include <iostream>
#include <vector>
//#include <cmath>

double quad_test_fn(int num_vars, int bits_per_var, double range_low_1, double range_high_1, double range_low_2, double range_high_2, std::vector<int> genes);
double quad_test_fn_real(int num_vars, double x[]);

#include <QFile>

class Escenario;

class TrainerAlgoritmoGenetico : public Trainer
{
    Q_OBJECT
public:
    explicit TrainerAlgoritmoGenetico(Simulador *sim_, QObject *parent = 0);
    float doSimulation(fuzzy &b, bool setSpinBox = true);
    float simulate(Escenario &e, fuzzy &b, double time);
    fuzzy best_fuzzy;
    float best_result;


protected:
    void run();
signals:
    
public slots:

private:
    QFile file;
    QString outputFileName;
    
};

#endif // TRAINERALGORITMOGENETICO_H
