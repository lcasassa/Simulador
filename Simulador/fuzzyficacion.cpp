#include "fuzzyficacion.h"
#include <QDebug>

Fuzzyficacion::Fuzzyficacion(QObject *parent) :
    QObject(parent)
{


    engine = new fl::Engine;
    engine->setName("simple-dimmer");
    engine->addHedge(new fl::Any);
    engine->addHedge(new fl::Extremely);
    engine->addHedge(new fl::Not);
    engine->addHedge(new fl::Seldom);
    engine->addHedge(new fl::Somewhat);
    engine->addHedge(new fl::Very);

    distancia = new fl::InputVariable;
    distancia->setName("Distancia");
    distancia->setRange(0.000, 1.000);
    distancia->addTerm(new fl::Triangle("CERCA",    0.00, 0.00, 0.50));
    distancia->addTerm(new fl::Triangle("PRUDENTE", 0.25, 0.50, 0.75));
    distancia->addTerm(new fl::Triangle("LEJOS",    0.55, 1.00, 1.00));
    engine->addInputVariable(distancia);

    vel = new fl::InputVariable;
    vel->setName("Velocidad");
    vel->setRange(-1.000, 1.000);
    vel->addTerm(new fl::Triangle("ACERCANDOSE", -1.00, -1.00, -0.25));
    vel->addTerm(new fl::Triangle("QUIETO",      -0.50,  0.00,  0.50));
    vel->addTerm(new fl::Triangle("ALEJANDOSE",   0.25,  1.00,  1.00));
    engine->addInputVariable(vel);



    out = new fl::OutputVariable;
    out->setName("Salida");
    out->setRange(-2.000, 1.000);
    out->setLockOutputRange(false);
    out->setDefaultValue(fl::nan);
    out->setLockValidOutput(false);
    out->setDefuzzifier(new fl::Centroid(500));
    out->output()->setAccumulation(new fl::Maximum);

    out->addTerm(new fl::Triangle("ALEJATE_MUCHO", -2.000, -1.000, 0.000));
    out->addTerm(new fl::Triangle("ALEJATE",       -1.000, -0.500, 0.000));
    out->addTerm(new fl::Triangle("NADA",          -0.500,  0.000, 0.500));
    out->addTerm(new fl::Triangle("ACERCATE",       0.000,  0.500, 1.000));
    engine->addOutputVariable(out);

    fl::RuleBlock* ruleblock1 = new fl::RuleBlock;
    ruleblock1->setName("");
    ruleblock1->setTnorm(new fl::Minimum);
    ruleblock1->setSnorm(new fl::Maximum);
    ruleblock1->setActivation(new fl::Minimum);

    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is CERCA    and Velocidad is ACERCANDOSE then Salida is ALEJATE_MUCHO", engine));
    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is CERCA    and Velocidad is QUIETO      then Salida is ALEJATE_MUCHO", engine));
    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is CERCA    and Velocidad is ALEJANDOSE  then Salida is ALEJATE", engine));
    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is PRUDENTE and Velocidad is ACERCANDOSE then Salida is ALEJATE_MUCHO", engine));
    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is PRUDENTE and Velocidad is ALEJANDOSE  then Salida is ACERCATE", engine));
    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is PRUDENTE and Velocidad is QUIETO      then Salida is ALEJATE", engine));
    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is LEJOS    and Velocidad is ACERCANDOSE then Salida is ALEJATE", engine));
    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is LEJOS    and Velocidad is ALEJANDOSE  then Salida is NADA", engine));
    ruleblock1->addRule(fl::FuzzyRule::parse("if Distancia is LEJOS    and Velocidad is QUIETO      then Salida is NADA", engine));
    engine->addRuleBlock(ruleblock1);

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





/* Entrada[4*4]
 *      4     3
 *   5   _______   2
 *  6   /       \   1
 *     /         \
 * 7   |         |   0
 *     |         |
 * 8   |         |  15
 *     \         /
 *  9   \_______/   14
 *   10          13
 *       11   12
 *
 *           ^
 * salida[1] |
 *           |
 *           ------> salida[0]
 */
void Fuzzyficacion::evaluar(qreal distancia_[4*4], qreal vel_[4*4], qreal out_[2]) {
    out_[0]  = 0;
    out_[0] += 2*fuzzyfica(distancia_[ 0], vel_[ 0]);
    out_[0] += 2*fuzzyfica(distancia_[ 1], vel_[ 1])*cos(30.0*M_PI/180.0);
    out_[0] += 2*fuzzyfica(distancia_[ 2], vel_[ 2])*cos(60.0*M_PI/180.0);
    out_[0] -= 2*fuzzyfica(distancia_[ 5], vel_[ 5])*cos(60.0*M_PI/180.0);
    out_[0] -= 2*fuzzyfica(distancia_[ 6], vel_[ 6])*cos(30.0*M_PI/180.0);
    out_[0] -= 2*fuzzyfica(distancia_[ 7], vel_[ 7]);
    out_[0] -= 2*fuzzyfica(distancia_[ 8], vel_[ 8]);
    out_[0] -= 2*fuzzyfica(distancia_[ 9], vel_[ 9])*cos(30.0*M_PI/180.0);
    out_[0] -= 2*fuzzyfica(distancia_[10], vel_[10])*cos(60.0*M_PI/180.0);
    out_[0] += 2*fuzzyfica(distancia_[13], vel_[13])*cos(60.0*M_PI/180.0);
    out_[0] += 2*fuzzyfica(distancia_[14], vel_[14])*cos(30.0*M_PI/180.0);
    out_[0] += 2*fuzzyfica(distancia_[15], vel_[15]);

    out_[1]  = 0;
    out_[1] += 2*fuzzyfica(distancia_[ 1], vel_[ 1])*sin(30.0*M_PI/180.0);
    out_[1] += 2*fuzzyfica(distancia_[ 2], vel_[ 2])*sin(60.0*M_PI/180.0);
    out_[1] += 2*fuzzyfica(distancia_[ 3], vel_[ 3]);
    out_[1] += 2*fuzzyfica(distancia_[ 4], vel_[ 4]);
    out_[1] += 2*fuzzyfica(distancia_[ 5], vel_[ 5])*sin(60.0*M_PI/180.0);
    out_[1] += 2*fuzzyfica(distancia_[ 6], vel_[ 6])*sin(30.0*M_PI/180.0);
    out_[1] -= 2*fuzzyfica(distancia_[ 9], vel_[ 9])*sin(30.0*M_PI/180.0);
    out_[1] -= 2*fuzzyfica(distancia_[10], vel_[10])*sin(60.0*M_PI/180.0);
    out_[1] -= 2*fuzzyfica(distancia_[11], vel_[11]);
    out_[1] -= 2*fuzzyfica(distancia_[12], vel_[12]);
    out_[1] -= 2*fuzzyfica(distancia_[13], vel_[13])*sin(60.0*M_PI/180.0);
    out_[1] -= 2*fuzzyfica(distancia_[14], vel_[14])*sin(30.0*M_PI/180.0);
}

float Fuzzyficacion::fuzzyfica(float distancia_, float vel_) {
    distancia->setInput(distancia_);
    vel->setInput(vel_);
    engine->process();
    float output = out->defuzzify();
    if(isnan(output))
        return 0;
    else
        return output;
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
