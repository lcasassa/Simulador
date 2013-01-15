#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QWidget>
#include <QThread>
#include <QList>
#include <QScopedPointer>

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
    void start();
    void stop();
    bool startStop();
    Ode *ode;

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;

signals:
    
public slots:
private slots:
    void timeout();
    
};

#endif // SIMULADOR_H
