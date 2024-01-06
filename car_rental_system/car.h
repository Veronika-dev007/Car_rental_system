#ifndef CAR_H
#define CAR_H

#include <QString>
#include <QStringList>

class Car
{

public:
    enum BodyType{//Перечисление
        SEDAN,//константы
        OFFROADCAR,
        MINIVAN,
        LIMOUSINE
    };

    Car();
    Car(QString id, QString brand, int BodyType, int year, int price);
    QString getId() const;
    BodyType getBodyType() const;
    QString getBodyTypeString() const;
    int getBasePrice() const;
    int getYear() const;
    QString getBrand() const;
    void setId(const QString &value);
    void setYear(const int &value);
    void setBasePrice(const int &value);
    void setBrand(const QString &value);
    QString getState() const;
    void setState(QString value);

private:
    BodyType carBodyType;
    int carBasePrice;
    int carYear;
    QString carBrand;
    QString carId;
    QString carState;
    QStringList type;

};

#endif // CAR_H
