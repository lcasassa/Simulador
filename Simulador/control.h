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
    virtual void loopControl(qreal *distanciaDetectado, qreal *salidas);
    virtual void pintar(QPainter *p);
signals:
    
public slots:
    
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CONTROL_H
