#include "plotfuzzy.h"

PlotFuzzy::PlotFuzzy(QWidget *parent) :
    QWidget(parent)
{
    estoesunascuantaaslineas.append(QLine(0,0,50,0));
}


void PlotFuzzy::paintEvent(QPaintEvent *event) {
    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    //foreach(QLine l,lines)
    //    painter.drawLine(l);
}
