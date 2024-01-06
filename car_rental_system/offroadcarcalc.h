#ifndef OFFROADCARCALC_H
#define OFFROADCARCALC_H

#include "abstractcalc.h"

class OffRoadCarCalc : public AbstractCalc
{
public:
    OffRoadCarCalc();
    int getCost(Car *value,const int period);
};

#endif // OFFROADCARCALC_H
