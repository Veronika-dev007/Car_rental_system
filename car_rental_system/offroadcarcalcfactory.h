#ifndef OFFROADCARCALCFACTORY_H
#define OFFROADCARCALCFACTORY_H

//#include "abstractcalc.h"
#include "calcfactory.h"
#include "offroadcarcalc.h"

class OffRoadCarCalcFactory : public CalcFactory
{
public:
    OffRoadCarCalcFactory();
    AbstractCalc* create();
};

#endif // OFFROADCARCALCFACTORY_H
