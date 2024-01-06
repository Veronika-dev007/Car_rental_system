#ifndef MINIVANCALC_H
#define MINIVANCALC_H

#include "abstractcalc.h"

class MinivanCalc : public AbstractCalc
{
public:
    MinivanCalc();
    int getCost(Car *value,const int period);
};

#endif // MINIVANCALC_H
