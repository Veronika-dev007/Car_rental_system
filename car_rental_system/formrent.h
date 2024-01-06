#ifndef FORMRENT_H
#define FORMRENT_H

#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <algorithm>
#include "calculationfacade.h"

#include "rent.h"
#include "rentmodel.h"

#include "carmodel.h"
#include "customermodel.h"

#include "rent.h"
#include "rentmodel.h"

namespace Ui {
class FormRent;
}

class FormRent : public QWidget
{
    Q_OBJECT

public:
    explicit FormRent(CarModel *mCar,CustomerModel *mCustomer,RentModel* mRent, const int row = -1,QWidget *parent = 0);
    ~FormRent();

signals:
    void notifyNewData(Rent*);
    void notifyUpdateData(Rent*);

private slots:
    void on_btnCalc_clicked();

    void on_btnOk_clicked();

    void on_cmbPassportId_currentIndexChanged(const QString &);

    void setBtnOkDisable();

private:
    Ui::FormRent *ui;
    CarModel *mCar;
    CustomerModel *mCustomer;
    RentModel *mRent;
    int currentRow;
    static int ID;

    CalculationFacade facade;

    void showCost(Car *car, const int days);
    Rent *processForm(const int row);
    void populateForm();
    void  setupEditForm();
    int setId();
};

#endif // FORMRENT_H
