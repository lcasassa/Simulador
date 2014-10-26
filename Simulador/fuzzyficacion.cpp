#include "fuzzyficacion.h"
#include <QDebug>

Fuzzyficacion::Fuzzyficacion(QObject *parent) :
    QObject(parent)
{


}

/*
f.input1[0][0] = 0.00;
f.input1[0][1] = 0.50;
f.input1[1][0] = 0.25;
f.input1[1][1] = 0.75;
f.input1[2][0] = 0.50;
f.input1[2][1] = 1.00;

f.input2[0][0] = -1.00;
f.input2[0][1] = -0.25;
f.input2[1][0] = -0.50;
f.input2[1][1] =  0.50;
f.input2[2][0] =  0.25;
f.input2[2][1] =  1.00;

f.output[0][0] = -2.00;
f.output[0][1] =  0.00;
f.output[1][0] = -1.00;
f.output[1][1] =  0.00;
f.output[2][0] = -0.50;
f.output[2][1] =  0.50;
f.output[3][0] =  0.00;
f.output[3][1] =  1.00;
*/
/*
QByteArray Fuzzyficacion::serialize(struct fuzzy f) {
    QByteArray b;
    QDataStream d(&b, QIODevice::WriteOnly);
    double *df = (double *)&f;
    for(unsigned int i=0; i < sizeof(struct fuzzy) / sizeof(double); i++) {
        double value = df[i];
        d << value;
    }
    return b;
}
*/
void Fuzzyficacion::setFuzzy(fuzzy &f) {
/*
    QDataStream d(b);
    struct fuzzy f;
    double *df = (double *)&f;
    for(unsigned int i=0; i < sizeof(struct fuzzy) / sizeof(double); i++) {
        double value;
        d >> value;
        df[i] = value;
    }
*/
/*
    struct fuzzy f;
    f.input1[0][0] = 0.00;
    f.input1[0][1] = 0.50;
    f.input1[1][0] = 0.25;
    f.input1[1][1] = 0.75;
    f.input1[2][0] = 0.50;
    f.input1[2][1] = 1.00;

    f.input2[0][0] = -1.00;
    f.input2[0][1] = -0.25;
    f.input2[1][0] = -0.50;
    f.input2[1][1] =  0.50;
    f.input2[2][0] =  0.25;
    f.input2[2][1] =  1.00;

    f.output[0][0] = -2.00;
    f.output[0][1] =  0.00;
    f.output[1][0] = -1.00;
    f.output[1][1] =  0.00;
    f.output[2][0] = -0.50;
    f.output[2][1] =  0.50;
    f.output[3][0] =  0.00;
    f.output[3][1] =  1.00;
*/

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
    distancia->addTerm(new fl::Triangle("CERCA",    f.input1[0][0], f.input1[0][0], f.input1[0][1]));
    distancia->addTerm(new fl::Triangle("PRUDENTE", f.input1[1][0], (f.input1[1][0] + f.input1[1][2]) / 2, f.input1[1][1]));
    distancia->addTerm(new fl::Triangle("LEJOS",    f.input1[2][0], f.input1[2][1], f.input1[2][1]));
    engine->addInputVariable(distancia);

    vel = new fl::InputVariable;
    vel->setName("Velocidad");
    vel->setRange(-1.000, 1.000);
    vel->addTerm(new fl::Triangle("ACERCANDOSE", f.input2[0][0], f.input2[0][0], f.input2[0][1]));
    vel->addTerm(new fl::Triangle("QUIETO",      f.input2[1][0], (f.input2[1][0] + f.input2[1][2]) / 2, f.input2[1][1]));
    vel->addTerm(new fl::Triangle("ALEJANDOSE",  f.input2[2][0], f.input2[2][1], f.input2[2][1]));
    engine->addInputVariable(vel);



    out = new fl::OutputVariable;
    out->setName("Salida");
    out->setRange(-2.000, 1.000);
    out->setLockOutputRange(false);
    out->setDefaultValue(fl::nan);
    out->setLockValidOutput(false);
    out->setDefuzzifier(new fl::Centroid(500));
    out->output()->setAccumulation(new fl::Maximum);

    out->addTerm(new fl::Triangle("ALEJATE_MUCHO", f.output[0][0], (f.output[0][0] + f.output[0][1]) / 2, f.output[0][1]));
    out->addTerm(new fl::Triangle("ALEJATE",       f.output[1][0], (f.output[1][0] + f.output[1][1]) / 2, f.output[1][1]));
    out->addTerm(new fl::Triangle("NADA",          f.output[2][0], (f.output[2][0] + f.output[2][1]) / 2, f.output[2][1]));
    out->addTerm(new fl::Triangle("ACERCATE",      f.output[3][0], (f.output[3][0] + f.output[3][1]) / 2, f.output[3][1]));
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
/*
    out_[0] = 0;
    out_[1] = 0;

    qreal x[2] = { 1,1 };
    x[0] *= distancia_[ 0]*cos( 0.0 * M_PI_2/180.0);
    x[0] *= distancia_[ 1]*cos(30.0 * M_PI_2/180.0);
    x[0] *= distancia_[ 2]*cos(60.0 * M_PI_2/180.0);
    x[0] *= distancia_[15]*cos( 0.0 * M_PI_2/180.0);
    x[0] *= distancia_[14]*cos(30.0 * M_PI_2/180.0);
    x[0] *= distancia_[13]*cos(60.0 * M_PI_2/180.0);

    x[1] *= distancia_[ 7]*cos( 0.0 * M_PI_2/180.0);
    x[1] *= distancia_[ 6]*cos(30.0 * M_PI_2/180.0);
    x[1] *= distancia_[ 5]*cos(60.0 * M_PI_2/180.0);
    x[1] *= distancia_[ 8]*cos( 0.0 * M_PI_2/180.0);
    x[1] *= distancia_[ 9]*cos(30.0 * M_PI_2/180.0);
    x[1] *= distancia_[10]*cos(60.0 * M_PI_2/180.0);

    qreal vx[2] = { 1,1 };
    vx[0] *= vel_[ 0]*cos( 0.0 * M_PI_2/180.0);
    vx[0] *= vel_[ 1]*cos(30.0 * M_PI_2/180.0);
    vx[0] *= vel_[ 2]*cos(60.0 * M_PI_2/180.0);
    vx[0] *= vel_[15]*cos( 0.0 * M_PI_2/180.0);
    vx[0] *= vel_[14]*cos(30.0 * M_PI_2/180.0);
    vx[0] *= vel_[13]*cos(60.0 * M_PI_2/180.0);

    vx[1] *= vel_[ 7]*cos( 0.0 * M_PI_2/180.0);
    vx[1] *= vel_[ 6]*cos(30.0 * M_PI_2/180.0);
    vx[1] *= vel_[ 5]*cos(60.0 * M_PI_2/180.0);
    vx[1] *= vel_[ 8]*cos( 0.0 * M_PI_2/180.0);
    vx[1] *= vel_[ 9]*cos(30.0 * M_PI_2/180.0);
    vx[1] *= vel_[10]*cos(60.0 * M_PI_2/180.0);

    out_[0] += fuzzyfica(x[0], vx[0]);
    out_[0] -= fuzzyfica(x[1], vx[1]);


    qreal y[2] = { 1,1 };
    y[0] *= distancia_[ 3]*cos( 0.0 * M_PI_2/180.0);
    y[0] *= distancia_[ 2]*cos(30.0 * M_PI_2/180.0);
    y[0] *= distancia_[ 1]*cos(60.0 * M_PI_2/180.0);
    y[0] *= distancia_[ 4]*cos( 0.0 * M_PI_2/180.0);
    y[0] *= distancia_[ 5]*cos(30.0 * M_PI_2/180.0);
    y[0] *= distancia_[ 6]*cos(60.0 * M_PI_2/180.0);

    y[1] *= distancia_[12]*cos( 0.0 * M_PI_2/180.0);
    y[1] *= distancia_[13]*cos(30.0 * M_PI_2/180.0);
    y[1] *= distancia_[14]*cos(60.0 * M_PI_2/180.0);
    y[1] *= distancia_[11]*cos( 0.0 * M_PI_2/180.0);
    y[1] *= distancia_[10]*cos(30.0 * M_PI_2/180.0);
    y[1] *= distancia_[ 9]*cos(60.0 * M_PI_2/180.0);

    qreal vy[2] = { 1,1 };
    vy[0] *= vel_[ 3]*cos( 0.0 * M_PI_2/180.0);
    vy[0] *= vel_[ 2]*cos(30.0 * M_PI_2/180.0);
    vy[0] *= vel_[ 1]*cos(60.0 * M_PI_2/180.0);
    vy[0] *= vel_[ 4]*cos( 0.0 * M_PI_2/180.0);
    vy[0] *= vel_[ 5]*cos(30.0 * M_PI_2/180.0);
    vy[0] *= vel_[ 6]*cos(60.0 * M_PI_2/180.0);

    vy[1] *= vel_[12]*cos( 0.0 * M_PI_2/180.0);
    vy[1] *= vel_[13]*cos(30.0 * M_PI_2/180.0);
    vy[1] *= vel_[14]*cos(60.0 * M_PI_2/180.0);
    vy[1] *= vel_[11]*cos( 0.0 * M_PI_2/180.0);
    vy[1] *= vel_[10]*cos(30.0 * M_PI_2/180.0);
    vy[1] *= vel_[ 9]*cos(60.0 * M_PI_2/180.0);

    out_[1] += fuzzyfica(y[0], vy[0]);
    out_[1] -= fuzzyfica(y[1], vy[1]);
*/
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
    if(distancia == NULL || vel == NULL || engine == NULL)
        return 0;

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
    delete engine;
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

#include <QFile>
#include <QTextStream>
void Fuzzyficacion::exportFuzzy(const fuzzy &f, QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

    QTextStream out(&file);
    for(int i=0; i<3; i++) {
       for(int j=0; j<2; j++) {
           out << f.input1[i][j] << "\n";
       }
    }
    for(int i=0; i<3; i++) {
       for(int j=0; j<2; j++) {
           out << f.input2[i][j] << "\n";
       }
    }
    file.close();
}

void Fuzzyficacion::importFuzzy(fuzzy &f, QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

    QTextStream in(&file);
    for(int i=0; i<3; i++) {
       for(int j=0; j<2; j++) {
           in >> f.input1[i][j];
       }
    }
    for(int i=0; i<3; i++) {
       for(int j=0; j<2; j++) {
           in >> f.input2[i][j];
       }
    }

    f.output[0][0] = -2.00;
    f.output[0][1] =  0.00;
    f.output[1][0] = -1.00;
    f.output[1][1] =  0.00;
    f.output[2][0] = -0.50;
    f.output[2][1] =  0.50;
    f.output[3][0] =  0.00;
    f.output[3][1] =  1.00;

    file.close();
}
