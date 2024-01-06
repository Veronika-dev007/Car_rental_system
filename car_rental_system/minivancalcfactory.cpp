#include "minivancalcfactory.h"

MinivanCalcFactory::MinivanCalcFactory(){}

AbstractCalc *MinivanCalcFactory::create()
{
    return new MinivanCalc();
}
