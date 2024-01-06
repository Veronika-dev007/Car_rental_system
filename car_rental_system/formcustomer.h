#ifndef FORMCUSTOMER_H
#define FORMCUSTOMER_H

#include <QWidget>
#include <QLineEdit>
#include <QRegExpValidator>
#include "customer.h"
#include "customermodel.h"

namespace Ui {
class FormCustomer;
}

class FormCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit FormCustomer(CustomerModel *model, const int row = -1,QWidget *parent = 0);
    ~FormCustomer();

signals:
    void notifyNewData(Customer*);
    void notifyUpdateData(Customer*);

private slots:
    void on_btnOk_clicked();


private:
    Ui::FormCustomer *ui;
    QList<QLineEdit*> lineEdits; // для хранения дочерних lineedit на форме
    CustomerModel *model;
    int currentRow;

    void setupValidation();//установка валидации - регудярок
    bool formIsFilled();
    bool searchId();
    Customer* processForm();
    void setupEditForm();
    void setupAddForm();
};

#endif // FORMCUSTOMER_H
