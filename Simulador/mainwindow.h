#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
     void closeEvent(QCloseEvent *event);
     void keyPressEvent(QKeyEvent* event);
     void keyReleaseEvent(QKeyEvent* event);

private slots:
     void on_spinBoxLoopSleepUs_valueChanged(int arg1);
     void on_pushButtonStart_clicked();
     void on_spinBoxRefrescoHz_valueChanged(int arg1);
     void on_pushButtonReset_clicked();
     void on_pushButtonStep_clicked();
     void on_pushButtonStartTraining_clicked();
     void trainerFinished();

     void on_pushButton_save_clicked();

     void on_pushButton_load_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
