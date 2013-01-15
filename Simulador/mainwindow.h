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
     void on_actionStart_Stop_triggered();

     void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
