#ifndef CALCFACTORY_H
#define CALCFACTORY_H

#include "abstractcalc.h"

class CalcFactory//абстрактный класс определяет абстрактный фабричный метод create(), который возвращает объект AbstractCalc.

{
public:
    CalcFactory();
    virtual AbstractCalc* create() = 0;
};

#endif // CALCFACTORY_H
