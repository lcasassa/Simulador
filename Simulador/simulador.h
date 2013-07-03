#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QWidget>
#include <QList>

#include "ode.h"
#include "trainer.h"
#include "objetofisico.h"

class Simulador : public QWidget
{
    Q_OBJECT
public:
    explicit Simulador(QWidget *parent = 0);
    ~Simulador();
    void registrarObjeto(ObjetoFisico *objetoFisico);
    QList<ObjetoFisico*> listaObjetoFisico;
    bool playPause();
    Ode *ode;
    Trainer *trainer;
    void setRefrescoHz(int refrescoHz);

public slots:
    void play();
    void step(int steps_ = 1);
    void pause();
    void reset();
    void stop();

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;

private slots:
    void timeout();
    
};

#endif // SIMULADOR_H
