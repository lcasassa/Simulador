#include "fuzzyficacion.h"
#include <QDebug>

Fuzzyficacion::Fuzzyficacion(QObject *parent) :
    QObject(parent)
{

    model = new fl::FuzzyEngine("", fl::FuzzyOperator::DefaultFuzzyOperator());

    energy = new fl::InputLVar("Distancia");
    energy->addTerm(new fl::ShoulderTerm("CERCA",  0.00, 1.00, true));
    energy->addTerm(new fl::TriangularTerm("BIEN", 1.00, 1.25));
    energy->addTerm(new fl::ShoulderTerm("LEJOS",  1.25, 2.00, false));
    model->addInputLVar(energy);

    health = new fl::OutputLVar("Salida");
    health->addTerm(new fl::TriangularTerm("ALEJATE_MUCHO", -2.00, -1.00));
    health->addTerm(new fl::TriangularTerm("ALEJATE",       -1.00,  -0.00));
    health->addTerm(new fl::TriangularTerm("NADA",           -1.00,  1.00));
    model->addOutputLVar(health);

    fl::MamdaniRule* rule1 = new fl::MamdaniRule();
    fl::MamdaniRule* rule2 = new fl::MamdaniRule();
    fl::MamdaniRule* rule3 = new fl::MamdaniRule();
    rule1->parse("if Distancia is CERCA then Salida is ALEJATE_MUCHO", *model);
    rule2->parse("if Distancia is BIEN then Salida is ALEJATE", *model);
    rule3->parse("if Distancia is LEJOS then Salida is NADA", *model);

    fl::RuleBlock* ruleblock = new fl::RuleBlock("Rules");
    ruleblock->addRule(rule1);
    ruleblock->addRule(rule2);
    ruleblock->addRule(rule3);
    model->addRuleBlock(ruleblock);

    /*
    fl::flScalar in;
    for(in = 0.0; in < 1.1; in += 0.1) {
        energy->setInput(in);
        model.process();
        fl::flScalar out = health->output().defuzzify();
        FL_LOG("Energy=" << in);
        FL_LOG("Energy is " << energy->fuzzify(in));
        FL_LOG("Health=" << out);
        FL_LOG("Health is " << health->fuzzify(out));
        FL_LOG("--");
    }
*/

}

void Fuzzyficacion::evaluar(qreal *distanciaDetectado, qreal *salidas) {
    energy->setInput(distanciaDetectado[0]);
    model->process();
    salidas[0] = health->output().defuzzify();

//    qWarning("%f -> %s -> %s-> %f", distanciaDetectado[0], energy->fuzzify(distanciaDetectado[0]).c_str(), health->fuzzify(salidas[0]).c_str(), salidas[0]);
}

Fuzzyficacion::~Fuzzyficacion() {
/*    for(int i=0; i<areaTriangular.size(); i++) {
        delete areaTriangular[i];
    }*/
}

/*
void Fuzzyficacion::addAreaTriangular(QString nombre_, qreal base1_, qreal base2_, qreal punta_) {
    AreaTriangular *areaNueva = new AreaTriangular;
    areaNueva->setTriangulo(nombre_, base1_, base2_, punta_);
    areaTriangular.append(areaNueva);
}

void Fuzzyficacion::addAreaTriangular(QString nombre_, qreal base1_, qreal base2_) {
    AreaTriangular *areaNueva = new AreaTriangular;
    areaNueva->setTriangulo(nombre_, base1_, base2_);
    areaTriangular.append(areaNueva);
}

void Fuzzyficacion::pintar(QPainter *p) {
    p->scale(5,2);
    p->setPen(Qt::red);
    QPointF points[4] = {
         QPointF(0.0, 0.0),
         QPointF(0.0, 1.0),
         QPointF(1.0, 1.0),
         QPointF(1.0, 0.0)
     };
    p->drawPolygon(points, 4);

    p->setPen(Qt::blue);
    p->setBrush(QBrush(Qt::yellow));
    for(int i=0; i<areaTriangular.size(); i++) {
        areaTriangular[i]->pintar(p);
    }
    p->scale(1,1);
}
*/
