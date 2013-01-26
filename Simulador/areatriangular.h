#ifndef AREATRIANGULAR_H
#define AREATRIANGULAR_H

#include <QObject>
#include <QPainter>
#include <ode/ode.h>

class AreaTriangular : public QObject
{
    Q_OBJECT
public:
    explicit AreaTriangular(QObject *parent = 0);
    ~AreaTriangular();
    void setTriangulo(QString nombre_, qreal base1_, qreal base2_, QPointF punta_);
    void setTriangulo(QString nombre_, qreal base1_, qreal base2_, qreal punta_);
    void setTriangulo(QString nombre_, qreal base1_, qreal base2_);
    dReal evalua(dReal x);
    void pintar(QPainter *p);

    QString nombre;

signals:
    
public slots:

private:
    QPointF base1;
    QPointF base2;
    QPointF punta;
    dReal entrada;
    dReal salida;
    static int id_count;
    int id;
};

#endif // AREATRIANGULAR_H
