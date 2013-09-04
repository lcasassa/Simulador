#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include "robotquadrotor.h"

void MainWindow::keyPressEvent(QKeyEvent* event)
{
//    qWarning("keyPressEvent %s", event->text().toAscii().data());
    if(event->key() == Qt::Key_Up) {
        RobotQuadrotor::key_up = true;
    } else if(event->key() == Qt::Key_Down) {
        RobotQuadrotor::key_down = true;
    } else if(event->key() == Qt::Key_Left) {
        RobotQuadrotor::key_left = true;
    } else if(event->key() == Qt::Key_Right) {
        RobotQuadrotor::key_right = true;
    } else if(event->key() == Qt::Key_S) {
        RobotQuadrotor::key_clock = true;
    } else if(event->key() == Qt::Key_A) {
        RobotQuadrotor::key_anticlock = true;
    } else if(event->key() == Qt::Key_F) {
        static bool isFullScreen = false;
        if(!isFullScreen)
            showFullScreen();
        else
            showNormal();
        isFullScreen = !isFullScreen;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
//    qWarning("keyPressEvent %s", event->text().toAscii().data());
    if(event->key() == Qt::Key_Up) {
        RobotQuadrotor::key_up = false;
    } else if(event->key() == Qt::Key_Down) {
        RobotQuadrotor::key_down = false;
    } else if(event->key() == Qt::Key_Left) {
        RobotQuadrotor::key_left = false;
    } else if(event->key() == Qt::Key_Right) {
        RobotQuadrotor::key_right = false;
    } else if(event->key() == Qt::Key_S) {
        RobotQuadrotor::key_clock = false;
    } else if(event->key() == Qt::Key_A) {
        RobotQuadrotor::key_anticlock = false;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //on_actionStart_Stop_triggered();
    setFocusPolicy(Qt::StrongFocus);

    int la = ui->spinBoxLoopSleepUs->value();
    ui->simuladorWidget->ode->sleepTime = la;
    ui->simuladorWidget->setRefrescoHz( ui->spinBoxRefrescoHz->value() );
    connect(ui->simuladorWidget->trainer, SIGNAL(finished()), this, SLOT(trainerFinished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qWarning("Esperando a que se cierre el thread");
    ui->simuladorWidget->stop();
}

void MainWindow::on_pushButtonStart_clicked()
{
    if( ui->simuladorWidget->playPause() ) {
        ui->pushButtonStart->setText("Stop");
    } else {
        ui->pushButtonStart->setText("Start");
    }
}

void MainWindow::on_spinBoxLoopSleepUs_valueChanged(int arg1)
{
    ui->simuladorWidget->ode->sleepTime = arg1;
}

void MainWindow::on_spinBoxRefrescoHz_valueChanged(int arg1)
{
    ui->simuladorWidget->setRefrescoHz(arg1);
}

void MainWindow::on_pushButtonReset_clicked()
{
    ui->simuladorWidget->reset();
    ui->pushButtonStart->setText("Start");
}

void MainWindow::on_pushButtonStep_clicked()
{
    ui->simuladorWidget->step( ui->spinBoxSteps->value() );
}

void MainWindow::on_pushButtonStartTraining_clicked()
{
    ui->pushButtonStartTraining->setEnabled(false);
    ui->simuladorWidget->trainer->start();
}

void MainWindow::trainerFinished() {
    ui->pushButtonStartTraining->setEnabled(true);
}

