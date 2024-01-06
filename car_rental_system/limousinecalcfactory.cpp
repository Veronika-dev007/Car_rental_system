#include "limousinecalcfactory.h"

LimousineCalcFactory::LimousineCalcFactory(){}

AbstractCalc *LimousineCalcFactory::create()
{
    return new LimousineCalc();
}
