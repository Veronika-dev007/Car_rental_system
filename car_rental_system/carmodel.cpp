#include "carmodel.h"

CarModel::CarModel(QObject *parent): QAbstractTableModel(parent){}

CarModel::CarModel(QList<Car *> initList, QObject *parent):
    QAbstractTableModel(parent),
    values(initList)
{
    header<<"Номер"<<"Марка"<<"Тип кузова"<<"Год выпуска"<<"Базовая цена"<<"Статус";
}

CarModel::~CarModel()
{
    qDeleteAll(values.begin(),values.end());
    values.clear();
}

int CarModel::rowCount(const QModelIndex &) const
{
    return values.count();//определение количества строк в модели
}

int CarModel::columnCount(const QModelIndex &) const
{
    return header.count();
}

//Функция data() отвечает за возвращение элемента данных, соответствующего запрошенному модельному индексу.
//Она вернёт непустое значение типа QVariant только если запрошенный модельный индекс валиден и требуемая роль поддерживается
QVariant CarModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

    if (index.row() >= values.size())
         return QVariant();

    if(role == Qt::DisplayRole ){
        switch(index.column()){
            case 0: return this->values.at(index.row())->getId();
            case 1: return this->values.at(index.row())->getBrand();
            case 2: return this->values.at(index.row())->getBodyTypeString();
            case 3: return this->values.at(index.row())->getYear();
            case 4: return this->values.at(index.row())->getBasePrice();
            case 5: return this->values.at(index.row())->getState();
            default: break;
            }
        }

    return QVariant();
}

QVariant CarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal && section < header.size())
        return QVariant(header.at(section));

    return QVariant();
}

void CarModel::append(Car *car)
{
    beginInsertRows(QModelIndex(), values.count(), values.count());
    values.append(car);
    endInsertRows();
    emit countChanged();
}

void CarModel::deleteRow(int idx)
{
    if (idx<0 || idx >= this->rowCount()) return;
    beginRemoveRows(QModelIndex(), idx, idx);
    values.removeAt(idx);
    endRemoveRows();
    emit countChanged();
}

void CarModel::update(int idx, Car *car)
{
    if (idx<0 || idx >= this->rowCount()) return;
    values[idx] = car;
    QModelIndex item_idx_s = this->index(idx,0);//первая ячейка строки
    QModelIndex item_idx_e = this->index(idx,this->columnCount(QModelIndex()));//последняя ячейка строки

    emit this->dataChanged(item_idx_s ,item_idx_e );//сигналу передаем диапазон строки которая изменилась

}

QList<Car *> CarModel::getCars() const
{
    return values;
}

Car *CarModel::getSelectedByCarId(QString id)
{
    //QString currId=this->index(row,0).data().toString();
    QList<Car*>::const_iterator it = std::find_if(values.begin(), values.end(), [id](Car* value)
    {
        return (value->getId() == id);
    });
    return *it;
}

Car *CarModel::getSelectedCar(const int row)
{
    QString id=this->index(row,0).data().toString();
    QList<Car*>::const_iterator it = std::find_if(values.begin(), values.end(), [id](Car* value)
    {
        return (value->getId() == id);
    });
    return *it;
}


