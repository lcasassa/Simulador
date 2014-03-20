#ifndef PLOTFUZZY_H
#define PLOTFUZZY_H

#include <QWidget>
//#include <QList>
//#include <QLine>
#include <QPainter>

class PlotFuzzy : public QWidget
{
    Q_OBJECT
public:
    PlotFuzzy(QWidget *parent = 0);
    float triangulos[3][3];
    void setDatos(int i, float x1, float x2, float x3, bool range=false);

signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *event);
private:
    int count;
    
};

#endif // PLOTFUZZY_H
