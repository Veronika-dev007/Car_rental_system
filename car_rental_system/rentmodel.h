#ifndef RENTMODEL_H
#define RENTMODEL_H

#include "rent.h"
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QStringList>

class RentModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    RentModel(QObject *parent = 0);
    RentModel(QList<Rent*> initList, QObject *parent = 0);
    ~RentModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(Rent *rent);
    void deleteRow(int idx);
    void update(int idx, Rent* rent);
    Rent* getSelectedRent(const int row);


signals:
    void countChanged();

private:
    QList<Rent*> values;
    QStringList header;

};

#endif // RENTMODEL_H
