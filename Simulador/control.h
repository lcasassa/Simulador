#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <QPainter>

class Control : public QWidget
{
    Q_OBJECT
public:
    explicit Control(QWidget *parent = 0);
    virtual ~Control();
    virtual void loopControl(qreal distancia_[4*4], qreal vel_[4*4], qreal out_[2]);
    virtual void pintar(QPainter *p);
signals:
    
public slots:
    
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CONTROL_H
