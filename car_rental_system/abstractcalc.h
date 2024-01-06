#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H

#include "car.h"
#include <QDate>

class AbstractCalc//определяет интерфейс класса, объекты которого надо создавать
{
public:
    AbstractCalc();
    virtual int getCost(Car*, const int period) = 0 ;
protected:
    int curYear;
};

#endif // ABSTRACTCALC_H
