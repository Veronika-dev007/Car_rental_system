#include "car.h"

Car::Car(){}

Car::Car(QString id, QString brand, int bodyType, int year, int price): carState("В наличии")
{
    carId=id;
    carBodyType=static_cast<BodyType>(bodyType);
    carBrand=brand;
    carYear=year;
    carBasePrice=price;
    type<<"Седан"<<"Внедорожник"<<"Минивэн"<<"Лимузин";
}

QString Car::getId() const
{
    return carId;
}

Car::BodyType Car::getBodyType() const
{
    return carBodyType;
}

QString Car::getBodyTypeString() const
{
    return type[carBodyType];
}

int Car::getBasePrice() const
{
    return carBasePrice;
}

int Car::getYear() const
{
    return carYear;
}

QString Car::getBrand() const
{
    return carBrand;
}

void Car::setId(const QString &value)
{
    carId=value;
}

void Car::setYear(const int &value)
{
    carYear=value;
}

void Car::setBasePrice(const int &value)
{
    carBasePrice=value;
}

void Car::setBrand(const QString &value)
{
    carBrand=value;
}

QString Car::getState() const
{
    return carState;
}

void Car::setState(QString value)
{
    carState = value;
}

