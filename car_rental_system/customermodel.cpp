#include "customermodel.h"

CustomerModel::CustomerModel(QObject *parent): QAbstractTableModel(parent){}

CustomerModel::CustomerModel(QList<Customer *> initList, QObject *parent):
    QAbstractTableModel(parent),
    values(initList)
{
    header<<"Номер паспорта"<<"ФИО"<<"Телефон"<<"Город";
}

CustomerModel::~CustomerModel()
{
    qDeleteAll(values.begin(),values.end());
    values.clear();
}

int CustomerModel::rowCount(const QModelIndex &parent) const
{
    return values.count();
}

int CustomerModel::columnCount(const QModelIndex &parent) const
{
    return header.count();
}

//Функция data() отвечает за возвращение элемента данных, соответствующего запрошенному модельному индексу.
//Она вернёт непустое значение типа QVariant только если запрошенный модельный индекс валиден и требуемая роль поддерживается
QVariant CustomerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

    if (index.row() >= values.size())
         return QVariant();

    if(role == Qt::DisplayRole ){
        switch(index.column()){
            case 0: return this->values.at(index.row())->getPassportId();
            case 1: return this->values.at(index.row())->getFullName();
            case 2: return this->values.at(index.row())->getPhone();
            case 3: return this->values.at(index.row())->getCity();
            case 4: return this->values.at(index.row())->getHasRent();
            default: break;
            }
        }

    return QVariant();
}

QVariant CustomerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal && section < header.size())
        return QVariant(header.at(section));

    return QVariant();
}

void CustomerModel::append(Customer *customer)
{
    beginInsertRows(QModelIndex(), values.count(), values.count());
    values.append(customer);
    endInsertRows();
    emit countChanged();
}

void CustomerModel::deleteRow(int idx)
{
    if (idx<0 || idx >= this->rowCount()) return;
    beginRemoveRows(QModelIndex(), idx, idx);
    values.removeAt(idx);
    endRemoveRows();
    emit countChanged();
}

void CustomerModel::update(int idx, Customer *customer)
{
    if (idx<0 || idx >= this->rowCount()) return;
    values[idx] = customer;
    QModelIndex item_idx_s = this->index(idx,0);//первая ячейка строки
    QModelIndex item_idx_e = this->index(idx,this->columnCount(QModelIndex()));//последняя ячейка строки

    emit this->dataChanged(item_idx_s ,item_idx_e );//сигналу передаем диапазон строки которая изменилась

}

Customer *CustomerModel::getSelectedCustomerById(QString id)
{
    QList<Customer*>::const_iterator it = std::find_if(values.begin(), values.end(), [id](Customer* value)
    {
        return (value->getPassportId() == id);
    });
    return *it;
}

Customer *CustomerModel::getSelectedCustomer(const int row)
{
    QString id=this->index(row,0).data().toString();
    QList<Customer*>::const_iterator it = std::find_if(values.begin(), values.end(), [id](Customer* value)
    {
        return (value->getPassportId() == id);
    });
    return *it;
}
