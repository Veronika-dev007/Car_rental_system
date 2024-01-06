#ifndef CUSTOMERMODEL_H
#define CUSTOMERMODEL_H

#include <customer.h>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QStringList>

class CustomerModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    CustomerModel(QObject *parent = 0);
    CustomerModel(QList<Customer*> initList, QObject *parent = 0);
    ~CustomerModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(Customer *customer);
    void deleteRow(int idx);
    void update(int idx, Customer *customer);
    Customer* getSelectedCustomerById(QString id);
    Customer* getSelectedCustomer(const int row);

signals:
    void countChanged();

private:
    QList<Customer*> values;
    QStringList header;

};

#endif // CUSTOMERMODEL_H
