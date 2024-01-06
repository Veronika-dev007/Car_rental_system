#ifndef SEDANCALCFACTORY_H
#define SEDANCALCFACTORY_H

//#include "abstractcalc.h"
#include "calcfactory.h"
#include "sedancalc.h"

class SedanCalcFactory : public CalcFactory//Конкретный класс - наследник класса CalcFactory, определяющий свою реализацию метода create().
{
public:
    SedanCalcFactory();
    AbstractCalc* create();
};

#endif // SEDANCALCFACTORY_H
