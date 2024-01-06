#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "carmodel.h"
#include "formcar.h"
#include "customermodel.h"
#include "formcustomer.h"
#include "rentmodel.h"
#include "reportmodel.h"
#include "formrent.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnAddCar_clicked();

    void on_btnEditCar_clicked();

    void on_btnDelCar_clicked();

    void on_btnAddCustomer_clicked();

    void on_btnDelCustomer_clicked();

    void on_btnEditCustomer_clicked();

    void on_btnAddRent_clicked();

    void on_btnDelRent_clicked();

    void on_btnEditRent_clicked();

public slots:
    void addCarToModel(Car* c);
    void updateCarModel(Car* c);

    void addCustomerToModel(Customer* c);
    void updateCustomerModel(Customer *c);

    void addRentToModel(Rent* r);
    void updateRentModel(Rent *r);


private:
    Ui::MainWindow *ui;
    CarModel *carModel;
    CustomerModel *customerModel;
    RentModel *rentModel;
    ReportModel* reportModel;

    QList<Car*> values;//для считывания исходных данных из csv файла
    QList<Customer*> listCustomers;//для считывания исходных данных из csv файла

    void setupCarModel();
    void showCarForm(int row = -1);

    void setupCustomerModel();
    void showCustomerForm(int row = -1);

    void setupRentModel();
    void showRentForm(int row = -1);

    void setupReportModel();

};

#endif // MAINWINDOW_H
