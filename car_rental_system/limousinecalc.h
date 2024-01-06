#ifndef LIMOUSINECALC_H
#define LIMOUSINECALC_H

#include "abstractcalc.h"

class LimousineCalc : public AbstractCalc
{
public:
    LimousineCalc();
    int getCost(Car *value,const int period);
};

#endif // LIMOUSINECALC_H
