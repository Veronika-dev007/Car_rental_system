#include "reportmodel.h"

ReportModel::ReportModel(QObject *parent): QAbstractTableModel(parent)
{
    header<<"Номер аренды"<<"Номер машины"<<"Номер паспорта"<<"Дата выдачи"<<"Дата возврата"<<"Цена"<<"Статус";
}

ReportModel::~ReportModel()
{
    values.clear();
}

int ReportModel::rowCount(const QModelIndex &parent) const
{
    return values.count();
}

int ReportModel::columnCount(const QModelIndex &parent) const
{
    return header.count();
}

QVariant ReportModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

    if (index.row() >= values.size())
         return QVariant();

    if(role == Qt::DisplayRole ){
        switch(index.column()){
            case 0: return this->values.at(index.row()).getRentId();
            case 1: return this->values.at(index.row()).getCarId();
            case 2: return this->values.at(index.row()).getPassportId();
            case 3: return this->values.at(index.row()).getTakeDate();
            case 4: return this->values.at(index.row()).getReturnDate();
            case 5: return this->values.at(index.row()).getPrice();
            case 6: return "Возвращён";
            default: break;
            }
        }

    return QVariant();
}

QVariant ReportModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal && section < header.size())
        return QVariant(header.at(section));

    return QVariant();
}

void ReportModel::append(Rent rent)
{
    beginInsertRows(QModelIndex(), values.count(), values.count());
    values.append(rent);
    endInsertRows();
    //emit countChanged();
}
