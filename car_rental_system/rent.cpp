#include "rent.h"

Rent::Rent(){}

Rent::Rent(int rentId, QString carId, QString passportId, QDate takeDate, QDate returnDate, QString price)
{
    this->rentId=rentId;
    this->carId=carId;
    this->passportId=passportId;
    this->takeDate=takeDate;
    this->returnDate=returnDate;
    this->price=price;
}

Rent::Rent(const Rent *r)
{
    this->rentId=r->rentId;
    this->carId=r->carId;
    this->passportId=r->passportId;
    this->takeDate=r->takeDate;
    this->returnDate=r->returnDate;
    this->price=r->price;
}

int Rent::getRentId() const
{
    return rentId;
}

void Rent::setRentId(const int &value)
{
    rentId = value;
}

QString Rent::getCarId() const
{
    return carId;
}

void Rent::setCarId(const QString &value)
{
    carId = value;
}

QString Rent::getPassportId() const
{
    return passportId;
}

void Rent::setPassportId(const QString &value)
{
    passportId = value;
}

QDate Rent::getTakeDate() const
{
    return takeDate;
}

void Rent::setTakeDate(const QDate &value)
{
    takeDate = value;
}

QDate Rent::getReturnDate() const
{
    return returnDate;
}

void Rent::setReturnDate(const QDate &value)
{
    returnDate = value;
}

QString Rent::getPrice() const
{
    return price;
}

void Rent::setPrice(const QString &value)
{
    price = value;
}


