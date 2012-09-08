#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QWidget>
#include <QThread>
#include <QList>

#include "ode.h"
#include "objetofisico.h"

class Simulador : public QWidget
{
    Q_OBJECT
public:
    explicit Simulador(QWidget *parent = 0);
    void registrarObjeto(ObjetoFisico *objetoFisico);
    QList<ObjetoFisico*> listaObjetoFisico;
    
protected:
    void paintEvent(QPaintEvent *);

private:
    Ode *ode;

signals:
    
public slots:
private slots:
    void timeout();
    
};

#endif // SIMULADOR_H
