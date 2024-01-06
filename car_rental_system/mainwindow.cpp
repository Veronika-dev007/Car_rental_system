#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupCarModel();
    setupCustomerModel();
    setupRentModel();
    setupReportModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupCarModel()
{
    values.append(new Car("1222","BMW",Car::BodyType::SEDAN,2023,1000000));
    values.append(new Car("3412","Lada",Car::BodyType::SEDAN,2022,900000));
    values.append(new Car("6726","Ford",Car::BodyType::OFFROADCAR,2020,1002000));
    values.append(new Car("3388","Mercedes",Car::BodyType::LIMOUSINE,2019,3000000));
    values.append(new Car("8999","Mercedes",Car::BodyType::MINIVAN,2020,4000000));

    carModel=new CarModel(values,this);
    ui->tableCar->setModel(carModel);
    ui->tableCar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//код одинаково растягивает каждый столбец, чтобы они соответствовали ширине таблицы

}

void MainWindow::on_btnAddCar_clicked()
{
    showCarForm();
}

void MainWindow::on_btnDelCar_clicked()
{
    QModelIndexList indexes = ui->tableCar->selectionModel()->selectedRows();//получаем индексы выбранных строк
    if(indexes.empty())
        QMessageBox::information(this,"Ошибка!", "Выберите запись для удаления.");
    else if(carModel->index(indexes[0].row(),5).data().toString()=="Выдан")
           QMessageBox::information(this,"Ошибка!", "Автомобиль с этой информацией уже выдан!\nДля удаления дождитесь возврата автомобиля.");
    else
        carModel->deleteRow(ui->tableCar->currentIndex().row());       
}

void MainWindow::on_btnEditCar_clicked()
{
    QModelIndexList indexes = ui->tableCar->selectionModel()->selectedRows();//получаем индексы выбранных строк
    if (indexes.empty())
        QMessageBox::information(this,"Ошибка!", "Выберите запись для редоктирования.");
    else if(carModel->index(indexes[0].row(),5).data().toString()=="Выдан")
           QMessageBox::information(this,"Ошибка!", "Автомобиль с этой информацией уже выдан!\nДля редактирования дождитесь возврата автомобиля.");
    else
        showCarForm(indexes[0].row());

}

void MainWindow::showCarForm(int row) {
    FormCar *formCar = new FormCar(carModel,row);//создаем объект - форму для машины
    formCar->setParent(this,Qt::Window);//устанавливаем родителя для формы

    connect(formCar, &FormCar::notifyNewData, this, &MainWindow::addCarToModel);
    connect(formCar, &FormCar::notifyUpdateData, this, &MainWindow::updateCarModel);

    QString title = (row == -1) ? tr("Добавить автомобиль") : tr("Редактировать автомобиль");

    formCar->setWindowTitle(title);
    formCar->show();
}

void MainWindow::addCarToModel(Car * c)
{
    carModel->append(c);
}

void MainWindow::updateCarModel(Car *c)
{
    carModel->update(ui->tableCar->currentIndex().row(),c);
}

void MainWindow::setupCustomerModel()
{
    listCustomers.append(new Customer("1242-432437","Петров И.С.","+79214564356","Москва"));
    listCustomers.append(new Customer("2222-438437","Лебедева А.Б.","+79298564356","СПб"));
    listCustomers.append(new Customer("3322-978777","Иванов П.Н.","+79214511156","Москва"));
    listCustomers.append(new Customer("2362-445366","Алексеев Д.Н.","+79314564786","Сочи"));

    customerModel=new CustomerModel(listCustomers,this);
    ui->tableCustomer->setModel(customerModel);
    ui->tableCustomer->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//код одинаково растягивает каждый столбец, чтобы они соответствовали ширине таблицы

}

void MainWindow::showCustomerForm(int row)
{
    FormCustomer *formCust = new FormCustomer(customerModel,row);
    formCust->setParent(this,Qt::Window);

    connect(formCust, &FormCustomer::notifyNewData, this, &MainWindow::addCustomerToModel);
    connect(formCust, &FormCustomer::notifyUpdateData, this, &MainWindow::updateCustomerModel);

    QString title = (row == -1) ? tr("Добавить клиента") : tr("Редактировать клиента");

    formCust->setWindowTitle(title);
    formCust->show();
}

void MainWindow::on_btnAddCustomer_clicked()
{
    showCustomerForm();
}

void MainWindow::on_btnDelCustomer_clicked()
{
    QModelIndexList indexes = ui->tableCustomer->selectionModel()->selectedRows();//получаем индексы выбранных строк
    Customer* c = customerModel->getSelectedCustomer(indexes[0].row());//получаем объект из выбранной строки
    if(indexes.empty())
            QMessageBox::information(this,"Ошибка!", "Выберите запись для удаления.");
    else if(c->getHasRent()>0)
           QMessageBox::information(this,"Ошибка!", "У клиента есть аренда автомобиля!\nДля удаления информации о клиенте, необходимо сначала оформить возврат автомобиля.");
    else
        customerModel->deleteRow(ui->tableCustomer->currentIndex().row());
}

void MainWindow::on_btnEditCustomer_clicked()
{
    QModelIndexList indexes = ui->tableCustomer->selectionModel()->selectedRows();
    if (!indexes.empty())
        showCustomerForm(indexes[0].row());
    else
        QMessageBox::information(this,"Ошибка!", "Выберите запись для редоктирования.");
}

void MainWindow::addCustomerToModel(Customer *c)
{
     customerModel->append(c);
}

void MainWindow::updateCustomerModel(Customer *c)
{
    customerModel->update(ui->tableCustomer->currentIndex().row(),c);
}

void MainWindow::setupRentModel()
{
    rentModel=new RentModel(this);
    ui->tableRent->setModel(rentModel);
    ui->tableRent->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//код одинаково растягивает каждый столбец, чтобы они соответствовали ширине таблицы

}

void MainWindow::showRentForm(int row)
{
    FormRent *formRent = new FormRent(carModel,customerModel,rentModel,row);
    formRent->setParent(this,Qt::Window);

    connect(formRent, &FormRent::notifyNewData, this, &MainWindow::addRentToModel);
    connect(formRent, &FormRent::notifyUpdateData, this, &MainWindow::updateRentModel);

    QString title = (row == -1) ? tr("Оформить новую аренду") : tr("Редактировать аренду");

    formRent->setWindowTitle(title);
    formRent->show();
}

void MainWindow::setupReportModel()
{
    reportModel=new ReportModel(this);
    ui->tableReport->setModel(reportModel);
    ui->tableReport->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//код одинаково растягивает каждый столбец, чтобы они соответствовали ширине таблицы

}

void MainWindow::addRentToModel(Rent *r)
{
    rentModel->append(r);
}

void MainWindow::updateRentModel(Rent *r)
{
    rentModel->update(ui->tableRent->currentIndex().row(),r);
}

void MainWindow::on_btnAddRent_clicked()
{
    showRentForm();
}

void MainWindow::on_btnDelRent_clicked()
{
    QModelIndexList indexes = ui->tableRent->selectionModel()->selectedRows();//получаем индексы выбранных строк
    if (indexes.empty())
        QMessageBox::information(this,"Ошибка!", "Выберите запись для удаления.");
    else{
         Car* c = carModel->getSelectedByCarId(rentModel->index(indexes[0].row(),1).data().toString());//получаем объект из выбранной строки
         c->setState("В наличии");
         Customer *customer = customerModel->getSelectedCustomerById(rentModel->index(indexes[0].row(),2).data().toString());
         customer->decreaseHasRent();
         Rent r(rentModel->getSelectedRent(indexes[0].row()));
         reportModel->append(r);
         rentModel->deleteRow(ui->tableRent->currentIndex().row());
    }
}

void MainWindow::on_btnEditRent_clicked()
{
    QModelIndexList indexes = ui->tableRent->selectionModel()->selectedRows();//получаем индексы выбранных строк
    if (!indexes.empty())
        showRentForm(indexes[0].row());
    else
         QMessageBox::information(this,"Ошибка!", "Выберите запись для редактирования.");
}
