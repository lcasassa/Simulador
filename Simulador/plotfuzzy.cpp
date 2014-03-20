#include "plotfuzzy.h"
#include <QLayout>
#include <QMargins>

PlotFuzzy::PlotFuzzy(QWidget *parent) :
    QWidget(parent)
{
    setDatos(0, 0.00, 0.25, 0.50);
    setDatos(1, 0.25, 0.50, 0.75);
    setDatos(2, 0.50, 0.75, 1.00);
}

void PlotFuzzy::setDatos(int i, float x1, float x2, float x3, bool range) {
    if(i>=3) return;
    if(range) {
        triangulos[i][0] = (x1+1)/2;
        triangulos[i][1] = (x2+1)/2;
        triangulos[i][2] = (x3+1)/2;
    } else {
        triangulos[i][0] = x1;
        triangulos[i][1] = x2;
        triangulos[i][2] = x3;
    }
}

void PlotFuzzy::paintEvent(QPaintEvent *event) {
    int w = width(); // 198
    int h = height(); // 94
    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width()*(0.1)/2, height()*(1-0.1));
    painter.scale(width()*(1-0.1)/100, -1*height()*(1-0.1));
    //painter.scale(side / 200.0, side / 200.0);

    for(int i=0; i<3; i++) {
        QPainterPath path;
        path.moveTo(triangulos[i][0]*100,0);
        path.lineTo(triangulos[i][2]*100,0);
        path.lineTo(triangulos[i][1]*100,1);
        path.lineTo(triangulos[i][0]*100,0);
        painter.setPen(Qt::NoPen);
        if(i==0) painter.fillPath(path, QBrush(QColor("blue")));
        else if(i==1) painter.fillPath(path, QBrush(QColor("green")));
        else if(i==2) painter.fillPath(path, QBrush(QColor("red")));
    }

    //foreach(QLine l,estoesunascuantaaslineas)
    //    painter.drawLine(l);
}
