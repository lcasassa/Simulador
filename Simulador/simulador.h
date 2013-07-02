#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QWidget>
#include <QList>

#include "ode.h"
#include "objetofisico.h"

class Simulador : public QWidget
{
    Q_OBJECT
public:
    explicit Simulador(QWidget *parent = 0);
    ~Simulador();
    void registrarObjeto(ObjetoFisico *objetoFisico);
    QList<ObjetoFisico*> listaObjetoFisico;
    void play();
    void step(int steps_ = 1);
    void pause();
    bool playPause();
    void reset();
    void stop();
    Ode *ode;
    void setRefrescoHz(int refrescoHz);

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;

private slots:
    void timeout();
    
};

#endif // SIMULADOR_H
