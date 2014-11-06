#include <QFile>
#include <QTextStream>
#include "fuzzyficacion.h"

int main(int argc, char *argv[])
{

    if(argc != 3) {
        qWarning("Error: pass two arguments: fuzzyFileName outputFileName");
        return 1;
    }

    QString fuzzyFileName(argv[1]);
    QString outputFileName(argv[2]);

    Fuzzyficacion fuzzyficacion;
    fuzzy b;

    Fuzzyficacion::importFuzzy(b, fuzzyFileName);
    fuzzyficacion.setFuzzy(b);

    QFile file(outputFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return 1;

    QTextStream out(&file);

    for(float distancia=0.0; distancia < 1.05; distancia += 0.05) {
        for(float vel=-1.0; vel < 1.05; vel += 0.05) {
            float result;
            result = fuzzyficacion.fuzzyfica(distancia, vel);
            out << distancia << "\t";
            out << vel << "\t";
            out << result << "\n";
        }
    }

    file.close();

    return 0;
}
