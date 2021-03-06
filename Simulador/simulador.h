#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QWidget>
#include <QList>

#include "ode.h"
#include "trainer.h"
#include "objetofisico.h"
#include "robotquadrotor.h"
#include "plotfuzzy.h"

namespace Ui {
 class MainWindow;
}

class Simulador : public QWidget
{
    Q_OBJECT
public:
    Simulador(QWidget *parent = 0);
    ~Simulador();

    bool playPause();
    bool odeRunning();
    void setRefrescoHz(int refrescoHz);

    QList<ObjetoFisico*> listaObjetoFisico;
    QMutex listaObjetoFisicoMutex;
    Ode *ode;
    Trainer *trainer;

    void setFuzzyWidgets(PlotFuzzy *plotFuzzyInput_, PlotFuzzy *plotFuzzyOutput_, PlotFuzzy *plotFuzzyInput2_, PlotFuzzy *plotFuzzyOutput2_);
    void setUI(Ui::MainWindow *ui_) { ui = ui_; }

    fuzzy fuzzyActual;
    fuzzy fuzzyBest;

public slots:
    void play(double sec);
    void step(int steps_ = 1);
    void pause();
    void reset();
    void stop();
    void destroyOde();
    void registrarObjeto(ObjetoFisico *objetoFisico);
    void desregistrarObjeto(ObjetoFisico *objetoFisico);
    void newFuzzy(fuzzy f, bool setSpinBox);
    void bestFuzzy(fuzzy f);

    void save(QString file);
    void load(QString file);

    Ui::MainWindow * getUI() { return ui; }

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;
    PlotFuzzy *plotFuzzyInput;
    PlotFuzzy *plotFuzzyOutput;
    PlotFuzzy *plotFuzzyInput2;
    PlotFuzzy *plotFuzzyOutput2;
    Ui::MainWindow *ui;

private slots:
    void timeout();

signals:
    void stopTrainer();
    
};

#endif // SIMULADOR_H
