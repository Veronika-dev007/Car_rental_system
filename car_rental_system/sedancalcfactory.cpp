#include "sedancalcfactory.h"

SedanCalcFactory::SedanCalcFactory()
{

}

AbstractCalc *SedanCalcFactory::create()
{
    return new SedanCalc();
}
