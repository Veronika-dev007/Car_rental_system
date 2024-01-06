#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class Customer
{
public:
    Customer();
    Customer(QString passportId, QString fullName, QString phone, QString city);
    QString getPassportId() const;
    QString getFullName() const;
    QString getPhone() const;
    QString getCity() const;
    void setPassportId(const QString &value);
    void setFullName(const QString &value);
    void setPhone(const QString &value);
    void setCity(const QString &value);
    int getHasRent() const;
    void increaseHasRent();
    void decreaseHasRent();

private:
    QString passportId;
    QString fullName;
    QString phone;
    QString city;
    int hasRent;
};

#endif // CUSTOMER_H
