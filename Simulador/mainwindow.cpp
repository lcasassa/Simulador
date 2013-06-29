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

    //ui->simuladorWidget->setControl(ui->widget_fuzzyfication);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qWarning("Esperando a que se cierre el thread");
    ui->simuladorWidget->stop();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->simuladorWidget->ode->sleepTime = arg1;
}
