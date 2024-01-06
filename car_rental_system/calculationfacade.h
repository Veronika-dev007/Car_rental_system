#ifndef CALCULATIONFACADE_H
#define CALCULATIONFACADE_H

#include <QObject>
#include "car.h"
#include "calcfactory.h"
#include "sedancalc.h"
#include "sedancalcfactory.h"
#include "offroadcarcalc.h"
#include "offroadcarcalcfactory.h"
#include "limousinecalc.h"
#include "limousinecalcfactory.h"
#include "minivancalc.h"
#include "minivancalcfactory.h"

class CalculationFacade: public QObject
{
     Q_OBJECT

public:
     explicit CalculationFacade(QObject *parent = 0);
     int getRentCost(Car* car, const int period);
};

#endif // CALCULATIONFACADE_H
