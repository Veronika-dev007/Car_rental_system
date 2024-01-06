#include "calculationfacade.h"

CalculationFacade::CalculationFacade(QObject *parent): QObject(parent){}

int CalculationFacade::getRentCost(Car *car, const int period)
{
    int cost;
    CalcFactory* creator;
    switch(car->getBodyType()){
    case Car::BodyType::SEDAN:{
        creator=new SedanCalcFactory();
       // AbstractCalc* sedan = creator->create();
        cost = creator->create()->getCost(car,period);
        break;
    }
    case Car::BodyType::OFFROADCAR:{
        creator=new OffRoadCarCalcFactory();
        AbstractCalc* road= creator->create();
        cost = road->getCost(car,period);
        break;
    }
    case Car::BodyType::MINIVAN:{
        creator=new MinivanCalcFactory();
        AbstractCalc* minivan= creator->create();
        cost = minivan->getCost(car,period);
        break;
    }
    case Car::BodyType::LIMOUSINE:{
        creator=new LimousineCalcFactory();
        AbstractCalc* lim= creator->create();
        cost = lim->getCost(car,period);
        break;
    }
    default:
        cost = -1;
        break;
    }
    return cost;
}

