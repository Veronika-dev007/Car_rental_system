#ifndef CARMODEL_H
#define CARMODEL_H

#include "car.h"
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QStringList>
#include <algorithm>

class CarModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    CarModel(QObject *parent = 0);
    CarModel(QList<Car*> initList, QObject *parent = 0);
    ~CarModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(Car *car);
    void deleteRow(int idx);
    void update(int idx, Car* car);
    QList<Car *> getCars() const;
    Car* getSelectedByCarId(QString id);
    Car* getSelectedCar(const int row);
signals:
    void countChanged();

private:
    QList<Car*> values;
    QStringList header;

};

#endif // CARMODEL_H
