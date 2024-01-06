#include "minivancalc.h"

MinivanCalc::MinivanCalc(){}

int MinivanCalc::getCost(Car *value, const int period)
{
    int cost;
    double depreciationFactor=0.5;//Коэффициент амортизации
    double profitFactor=1.05; //Планируемая рентабельность (прибыль)
    cost = value->getBasePrice()*depreciationFactor*profitFactor*0.02;

    int ageOfCar=curYear-value->getYear();

    if(ageOfCar<4)
        cost*=0.12;
    else if(ageOfCar<6)
        cost*=0.09;
    else
        cost*=0.07;

    return cost*period;
}
