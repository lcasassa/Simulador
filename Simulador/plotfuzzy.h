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
    QList<QLine> estoesunascuantaaslineas;
    
signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *event);
    
};

#endif // PLOTFUZZY_H
