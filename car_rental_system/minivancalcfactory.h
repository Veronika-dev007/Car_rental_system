#ifndef MINIVANCALCFACTORY_H
#define MINIVANCALCFACTORY_H

//#include "abstractcalc.h"
#include "calcfactory.h"
#include "minivancalc.h"

class MinivanCalcFactory : public CalcFactory
{
public:
    MinivanCalcFactory();
    AbstractCalc* create();
};

#endif // MINIVANCALCFACTORY_H
