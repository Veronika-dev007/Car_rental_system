#include "limousinecalc.h"

LimousineCalc::LimousineCalc(){}

int LimousineCalc::getCost(Car *value, const int period)
{
    int cost;
    double depreciationFactor=0.2;//Коэффициент амортизации
    double profitFactor=1.2; //Планируемая рентабельность (прибыль)
    cost = value->getBasePrice()*depreciationFactor*profitFactor*0.02;

    int ageOfCar=curYear-value->getYear();

    if(ageOfCar<4)
        cost*=0.11;
    else if(ageOfCar<6)
        cost*=0.1;
    else
        cost*=0.07;

    return cost*period;
}
