#include "rentmodel.h"

RentModel::RentModel(QObject *parent): QAbstractTableModel(parent)
{
    header<<"Номер аренды"<<"Номер машины"<<"Номер паспорта"<<"Дата выдачи"<<"Дата возврата"<<"Цена";
}

RentModel::RentModel(QList<Rent *> initList, QObject *parent):
    QAbstractTableModel(parent),
    values(initList)
{
    header<<"Номер аренды"<<"Номер машины"<<"Номер паспорта"<<"Дата выдачи"<<"Дата возврата"<<"Цена";
}

RentModel::~RentModel()
{
    qDeleteAll(values.begin(),values.end());
    values.clear();
}

int RentModel::rowCount(const QModelIndex &parent) const
{
     return values.count();
}

int RentModel::columnCount(const QModelIndex &parent) const
{
     return header.count();
}

//Функция data() отвечает за возвращение элемента данных, соответствующего запрошенному модельному индексу.
//Она вернёт непустое значение типа QVariant только если запрошенный модельный индекс валиден и требуемая роль поддерживается
QVariant RentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

    if (index.row() >= values.size())
         return QVariant();

    if(role == Qt::DisplayRole ){
        switch(index.column()){
            case 0: return this->values.at(index.row())->getRentId();
            case 1: return this->values.at(index.row())->getCarId();
            case 2: return this->values.at(index.row())->getPassportId();
            case 3: return this->values.at(index.row())->getTakeDate();
            case 4: return this->values.at(index.row())->getReturnDate();
            case 5: return this->values.at(index.row())->getPrice();
            default: break;
            }
        }

    return QVariant();
}

QVariant RentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal && section < header.size())
        return QVariant(header.at(section));

    return QVariant();
}

void RentModel::append(Rent *rent)
{
    beginInsertRows(QModelIndex(), values.count(), values.count());
    values.append(rent);
    endInsertRows();
    emit countChanged();
}

void RentModel::deleteRow(int idx)
{
    if (idx<0 || idx >= this->rowCount()) return;
    beginRemoveRows(QModelIndex(), idx, idx);
    values.removeAt(idx);
    endRemoveRows();
    emit countChanged();
}

void RentModel::update(int idx, Rent *rent)
{
    if (idx<0 || idx >= this->rowCount()) return;
    values[idx] = rent;
    QModelIndex item_idx_s = this->index(idx,0);//первая ячейка строки
    QModelIndex item_idx_e = this->index(idx,this->columnCount(QModelIndex()));//последняя ячейка строки

    emit this->dataChanged(item_idx_s ,item_idx_e );//сигналу передаем диапазон строки которая изменилась

}

Rent *RentModel::getSelectedRent(const int row)
{
    QString id=this->index(row,0).data().toString();
    QList<Rent*>::const_iterator it = std::find_if(values.begin(), values.end(), [id](Rent* value)
    {
        return (QString::number(value->getRentId()) == id);
    });
    return *it;
}
