#ifndef LIMOUSINECALCFACTORY_H
#define LIMOUSINECALCFACTORY_H

//#include "abstractcalc.h"
#include "calcfactory.h"
#include "limousinecalc.h"

class LimousineCalcFactory : public CalcFactory
{
public:
    LimousineCalcFactory();
    AbstractCalc* create();
};

#endif // LIMOUSINECALCFACTORY_H
