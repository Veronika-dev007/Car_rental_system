#include "offroadcarcalcfactory.h"

OffRoadCarCalcFactory::OffRoadCarCalcFactory(){}

AbstractCalc *OffRoadCarCalcFactory::create()
{
    return new OffRoadCarCalc();
}
