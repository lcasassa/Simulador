#ifndef TRAINER_H
#define TRAINER_H

#include <QThread>

class Trainer : public QThread
{
    Q_OBJECT
public:
    explicit Trainer(QObject *parent = 0);
    ~Trainer();

protected:
    void run();
    
signals:
    void playOde();
    void stopOde();
    void pauseOde();
    void resetOde();
    
public slots:
    
};

#endif // TRAINER_H
