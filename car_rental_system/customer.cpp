#include "customer.h"

int Customer::getHasRent() const
{
    return hasRent;
}

void Customer::increaseHasRent()
{
    hasRent++;
}

void Customer::decreaseHasRent()
{
    hasRent--;
}

Customer::Customer(){ }

Customer::Customer(QString passportId, QString fullName, QString phone, QString city)
{
    this->passportId=passportId;
    this->fullName=fullName;
    this->phone=phone;
    this->city=city;
    this->hasRent=0;
}

QString Customer::getPassportId() const
{
    return passportId;
}

void Customer::setPassportId(const QString &value)
{
    passportId = value;
}

QString Customer::getFullName() const
{
    return fullName;
}

void Customer::setFullName(const QString &value)
{
    fullName = value;
}

QString Customer::getPhone() const
{
    return phone;
}

QString Customer::getCity() const
{
    return city;
}

void Customer::setPhone(const QString &value)
{
    phone = value;
}

void Customer::setCity(const QString &value)
{
    city = value;
}
