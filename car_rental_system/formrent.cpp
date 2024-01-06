#include "formrent.h"
#include "ui_formrent.h"

int FormRent::ID=100;

FormRent::FormRent(CarModel *mCar, CustomerModel *mCustomer, RentModel *mRent, const int row, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRent),
    mCar(mCar),
    mCustomer(mCustomer),
    mRent(mRent),
    currentRow(row)
{
    ui->setupUi(this);

    if(currentRow==-1)
        populateForm();//настройки для формы в случае добавления
    else
        setupEditForm(); //предворительное заполнение формы перед редактированием

    ui->btnOk->setDisabled(true);
    connect(ui->btnCancel,&QPushButton::clicked,this,&FormRent::close);
    connect(ui->dateTake,&QDateEdit::dateChanged,this,&FormRent::setBtnOkDisable);
    connect(ui->dateReturn,&QDateEdit::dateChanged,this,&FormRent::setBtnOkDisable);
    connect(ui->dateTake,&QDateEdit::dateChanged,[&](){ui->lblCalc->clear();});
    connect(ui->dateReturn,&QDateEdit::dateChanged,[&](){ui->lblCalc->clear();});
    connect(ui->dateTake,&QDateEdit::dateChanged,[&](){ui->lblCountDays->clear();});
    connect(ui->dateReturn,&QDateEdit::dateChanged,[&](){ui->lblCountDays->clear();});
    connect(ui->cmbPassportId,static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged),this,&FormRent::setBtnOkDisable);
}

FormRent::~FormRent()
{
    delete ui;
}

void FormRent::populateForm()
{
    ui->tableChooseCar->setModel(mCar);
    ui->tableChooseCar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//код одинаково растягивает каждый столбец, чтобы они соответствовали ширине таблицы
    ui->tableChooseCar->resizeColumnsToContents();
    connect(ui->tableChooseCar,&QTableView::clicked,this,&FormRent::setBtnOkDisable);

    int row_count = mCar->rowCount();
    for( int i = 0; i < row_count; i++ )
    {
        QModelIndex idx = mCar->index( i, 5 );//i- строка, 5 -столбец
        if( mCar->data(idx, Qt::DisplayRole).toString() == "Выдан" )
        {
             ui->tableChooseCar->hideRow(i);
        }
    }

    ui->cmbPassportId->setModel(mCustomer);
    ui->cmbPassportId->setCurrentIndex(0);

    ui->dateTake->setDate(QDate::currentDate());
    ui->dateReturn->setDate(QDate::currentDate());
    ui->dateTake->setDisplayFormat("d MMM yyyy");
    ui->dateReturn->setDisplayFormat("d MMM yyyy");
}

void FormRent::setupEditForm()
{
    ui->tableChooseCar->setModel(mCar);
    ui->tableChooseCar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//код одинаково растягивает каждый столбец, чтобы они соответствовали ширине таблицы
    ui->tableChooseCar->resizeColumnsToContents();


    int row_count = mCar->rowCount();
    QVariant search=mRent->index(currentRow,1).data();
    for( int i = 0; i < row_count; i++ )
    {
        QModelIndex idx = mCar->index( i, 0 );//i- строка, 0 -столбец
        if( mCar->data(idx, Qt::DisplayRole).toString() != search )
            ui->tableChooseCar->hideRow(i);
        else
            ui->tableChooseCar->setCurrentIndex(idx); //по умолчание устанавливаем текущий индек выбраным
    }

    ui->cmbPassportId->setModel(mCustomer);
    ui->cmbPassportId->setCurrentText(mRent->index(currentRow,2).data().toString());

    ui->dateTake->setDate(mRent->index(currentRow,3).data().toDate());
    ui->dateReturn->setDate(mRent->index(currentRow,4).data().toDate());
    ui->dateTake->setDisplayFormat("d MMM yyyy");
    ui->dateReturn->setDisplayFormat("d MMM yyyy");
}

void FormRent::on_btnCalc_clicked()
{
    QDate start=ui->dateTake->date();
    QDate end=ui->dateReturn->date();
    int days=start.daysTo(end);
    if(days>0)
        ui->lblCountDays->setText("Количество дней: "+QString::number(days));
    else{
        QMessageBox::information(this,"Ошибка!", "Указан некорректный период аренды.");
        return;
    }

    QModelIndexList indexes = ui->tableChooseCar->selectionModel()->selectedRows();
    if(!indexes.empty()){
        showCost(mCar->getSelectedCar(indexes[0].row()),days);
        ui->btnOk->setEnabled(true);
    }
    else
         QMessageBox::information(this,"Ошибка!", "Выберите автомобиль.");
}

Rent *FormRent::processForm(const int row)
{
    return new Rent(setId(),
                    mCar->index(row,0).data().toString(),
                    ui->cmbPassportId->currentText(),
                    ui->dateTake->date(),
                    ui->dateReturn->date(),
                    ui->lblCalc->text());
}

int FormRent::setId()
{
    if(currentRow==-1)
        return ID++;
    else
        return mRent->index(currentRow,0).data().toInt();
}

void FormRent::showCost(Car* car,const int days){
    ui->lblCalc->setText(QString::number(facade.getRentCost(car,days))+" руб.");//обращение к фасаду для расчета стоимости
}

void FormRent::on_btnOk_clicked()
{
   QModelIndexList indexes = ui->tableChooseCar->selectionModel()->selectedRows();
   if(currentRow==-1)
   {
        emit notifyNewData(processForm(indexes[0].row()));//испускаем сигнал
        mCar->getSelectedCar(indexes[0].row())->setState("Выдан");
        Customer* c =  mCustomer->getSelectedCustomerById(ui->cmbPassportId->currentText());
        c->increaseHasRent();
   }
   else
   {
        emit notifyUpdateData(processForm(indexes[0].row()));//испускаем сигнал
   }
   this->close();
}

void FormRent::on_cmbPassportId_currentIndexChanged(const QString &)
{
    int row = ui->cmbPassportId->currentIndex();
    ui->lblFullName->setText("ФИО: " + mCustomer->index(row,1).data().toString());
    ui->btnOk->setEnabled(false);
}

void FormRent::setBtnOkDisable()
{
    ui->btnOk->setDisabled(true);
}


