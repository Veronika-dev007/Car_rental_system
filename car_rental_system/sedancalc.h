#ifndef SEDANCALC_H
#define SEDANCALC_H

#include "abstractcalc.h"

class SedanCalc: public AbstractCalc //Конкретные класс представляющий реализацию класса AbstractCalc
{
public:
    SedanCalc();
    int getCost(Car *value,const int period);
};

#endif // SEDANCALC_H
