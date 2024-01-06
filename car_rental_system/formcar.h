#ifndef FORMCAR_H
#define FORMCAR_H

#include <QWidget>
#include <QLineEdit>
#include <QRegExpValidator>
#include "car.h"
#include "carmodel.h"

namespace Ui {
class FormCar;
}

class FormCar : public QWidget
{
    Q_OBJECT

public:
    explicit FormCar(CarModel *model, const int row = -1, QWidget *parent = 0);
    ~FormCar();

signals:
    void notifyNewData(Car*);
    void notifyUpdateData(Car*);

private slots:
    void on_btnOk_clicked();

private:
    Ui::FormCar *ui;
    QList<QLineEdit*> lineEdits; // для хранения дочерних lineedit на форме
    CarModel *model;
    int currentRow;

    void setupValidation();//установка валидации - регудярок
    bool formIsFilled();
    bool searchId();
    Car* processForm();
    void setupForm();

};

#endif // FORMCAR_H
