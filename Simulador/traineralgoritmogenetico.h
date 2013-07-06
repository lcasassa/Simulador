#ifndef TRAINERALGORITMOGENETICO_H
#define TRAINERALGORITMOGENETICO_H

#include "trainer.h"

class TrainerAlgoritmoGenetico : public Trainer
{
    Q_OBJECT
public:
    explicit TrainerAlgoritmoGenetico(QObject *parent = 0);
    
protected:
    void run();
signals:
    
public slots:
    
};

#endif // TRAINERALGORITMOGENETICO_H
