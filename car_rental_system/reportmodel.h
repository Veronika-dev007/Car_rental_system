#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include "rent.h"
#include <QObject>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QStringList>

class ReportModel : public QAbstractTableModel
{
public:
    ReportModel(QObject *parent = 0);
    ~ReportModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(Rent rent);

signals:
    void countChanged();

private:
    QList<Rent> values;
    QStringList header;

};

#endif // REPORTMODEL_H
