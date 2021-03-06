#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include "robotquadrotor.h"
#include <QTimer>

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
    ui->simuladorWidget->setFuzzyWidgets(ui->widgetInput, ui->widgetOutput, ui->widgetInput2, ui->widgetOutput2);
    ui->simuladorWidget->setUI(ui);

    //on_actionStart_Stop_triggered();
    setFocusPolicy(Qt::StrongFocus);

    ui->simuladorWidget->ode->sleepTime = ui->spinBoxLoopSleepUs->value();
    ui->simuladorWidget->setRefrescoHz( ui->spinBoxRefrescoHz->value() );
    connect(ui->simuladorWidget->trainer, SIGNAL(finished()), this, SLOT(trainerFinished()));

    QTimer::singleShot(500, this, SLOT(on_pushButtonStartTraining_clicked()));
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
    //showFullScreen();
}

void MainWindow::trainerFinished() {
    ui->pushButtonStartTraining->setEnabled(true);
}


void MainWindow::on_pushButton_save_clicked()
{
    int slot = -1;
    if(ui->radioButton->isChecked())
        slot = 1;
    else if(ui->radioButton_2->isChecked())
        slot = 2;
    else if(ui->radioButton_3->isChecked())
        slot = 3;

    QString file(QString("savefile_") + QString::number(slot) + ".bin");
    ui->simuladorWidget->save(file);

    qWarning("Saved to file %d", slot);
}

void MainWindow::on_pushButton_load_clicked()
{
    int slot = -1;
    if(ui->radioButton->isChecked())
        slot = 1;
    else if(ui->radioButton_2->isChecked())
        slot = 2;
    else if(ui->radioButton_3->isChecked())
        slot = 3;

    QString file(QString("savefile_") + QString::number(slot) + ".bin");
    ui->simuladorWidget->load(file);

    qWarning("Loaded from file %d", slot);
}
