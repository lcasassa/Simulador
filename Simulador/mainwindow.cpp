#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_actionStart_Stop_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qWarning("Esperando a que se cierre el thread");
    ui->simuladorWidget->stop();
}

void MainWindow::on_actionStart_Stop_triggered()
{
    if(ui->simuladorWidget->startStop()) {
        ui->actionStart_Stop->setText("Stop");
    } else {
        ui->actionStart_Stop->setText("Start");
    }
}
