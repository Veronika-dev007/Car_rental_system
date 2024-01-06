#include "formcar.h"
#include "ui_formcar.h"

FormCar::FormCar(CarModel* model, int const row, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCar),
    model(model),
    currentRow(row)
{
    ui->setupUi(this);
    setupValidation();

    if(currentRow!=-1)
        setupForm();//настройки формы в случае редактирования
    else
        ui->lineId->setPlaceholderText("1234");

    lineEdits =this->findChildren<QLineEdit*>();//находим все LineEdits на форме

    for (QLineEdit *lineEdit : lineEdits)
        connect(lineEdit,&QLineEdit::textChanged,[&](){ui->lblError->clear();});
}

FormCar::~FormCar()
{
    delete ui;
}

void FormCar::setupValidation()
{
    //проверка ввода на соответствие регулярному выражению
    ui->lineId->setValidator(new QRegExpValidator(QRegExp("\\d{4}"),this));
    ui->lineBrand->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-ЯёЁ-]+"),this));
    ui->lineYear->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
    ui->lineBasePrice->setValidator(new QRegExpValidator(QRegExp("\\d+"),this));
}

bool FormCar::formIsFilled()
{
    for (QLineEdit *lineEdit : lineEdits) {
        if(lineEdit->text().isEmpty())
            return false;
    }
    return true;
}

Car* FormCar::processForm(){
    return new Car(ui->lineId->text(),
                   ui->lineBrand->text(),
                   ui->cmbBType->currentIndex(),
                   ui->lineYear->text().toInt(),
                   ui->lineBasePrice->text().toInt());
}

void FormCar::setupForm()
{
    ui->lineId->setText(model->index(currentRow,0).data().toString());
    ui->lineBrand->setText(model->index(currentRow,1).data().toString());
    ui->cmbBType->setCurrentText(model->index(currentRow,2).data().toString());
    ui->lineYear->setText(model->index(currentRow,3).data().toString());
    ui->lineBasePrice->setText(model->index(currentRow,4).data().toString());
}

bool FormCar::searchId()
{
       int row_count = model->rowCount();
       QString search = ui->lineId->text();
       for( int i = 0; i < row_count; i++ )
       {
           QModelIndex idx = model->index( i, 0 );//i- строка, 0 -столбец
           if( model->data(idx, Qt::DisplayRole).toString() == search )
           {
              return true;
           }
       }
       return false;
}
void FormCar::on_btnOk_clicked()
{
    if(!formIsFilled())
    {
        ui->lblError->setText("Заполните все поля формы!");
        return;
    }

    if(currentRow!=-1){
        emit notifyUpdateData(processForm());//испускаем сигнал
        this->close();
        return;
    }

    if(currentRow==-1 && searchId())
    {
        ui->lblError->setText("Автомобиль с таким номером уже есть!");
    }
    else
    {
        emit notifyNewData(processForm());//испускаем сигнал
        this->close();
    }

}

