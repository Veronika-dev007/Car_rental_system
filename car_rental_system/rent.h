#ifndef RENT_H
#define RENT_H

#include <QString>
#include <QDate>

class Rent
{
public:
    Rent();
    Rent( int rentId, QString carId, QString passportId, QDate takeDate, QDate returnDate, QString price);
    Rent(const Rent *r);
    int getRentId() const;
    void setRentId(const int &value);
    QString getCarId() const;
    void setCarId(const QString &value);
    QString getPassportId() const;
    void setPassportId(const QString &value);
    QDate getTakeDate() const;
    void setTakeDate(const QDate &value);
    QDate getReturnDate() const;
    void setReturnDate(const QDate &value);
    QString getPrice() const;
    void setPrice(const QString &value);

private:
    int rentId;
    QString carId;
    QString passportId;
    QDate takeDate;
    QDate returnDate;
    QString price;
};

#endif // RENT_H
