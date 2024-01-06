#include "formcustomer.h"
#include "ui_formcustomer.h"

FormCustomer::FormCustomer(CustomerModel *model, const int row, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCustomer),
    model(model),
    currentRow(row)
{
    ui->setupUi(this);
    setupValidation();

    if(currentRow!=-1)
        setupEditForm();//настройки для формы в случае редактирования
    else
        setupAddForm();//настройки для формы в случае добавления

    lineEdits =this->findChildren<QLineEdit*>();//находим все LineEdits на форме

    for (QLineEdit *lineEdit : lineEdits)
        connect(lineEdit,&QLineEdit::textChanged,[&](){ui->lblError->clear();});
}

FormCustomer::~FormCustomer()
{
    delete ui;
}

void FormCustomer::setupValidation()
{
    //проверка ввода на соответствие регулярному выражению
    ui->linePassportId->setValidator(new QRegExpValidator(QRegExp("\\d{4}-\\d{6}"),this));
    ui->lineName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-ЯёЁ.\\s]+"),this));
    ui->linePhone->setValidator(new QRegExpValidator(QRegExp("\\+\\d+"),this));
    ui->lineCity->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-ЯёЁ-]+"),this));
}

bool FormCustomer::formIsFilled()
{
    for (QLineEdit *lineEdit : lineEdits) {
        if(lineEdit->text().isEmpty())
            return false;
    }
    return true;
}

Customer* FormCustomer::processForm(){
    return new Customer(ui->linePassportId->text(),
                   ui->lineName->text(),
                   ui->linePhone->text(),
                   ui->lineCity->text());
}

void FormCustomer::setupEditForm()
{
    ui->linePassportId->setText(model->index(currentRow,0).data().toString());
    ui->lineName->setText(model->index(currentRow,1).data().toString());
    ui->linePhone->setText(model->index(currentRow,2).data().toString());
    ui->lineCity->setText(model->index(currentRow,3).data().toString());
    Customer* c = model->getSelectedCustomer(currentRow);
    if(c->getHasRent()>0)
            ui->linePassportId->setReadOnly(true);
}

void FormCustomer::setupAddForm()
{
    ui->linePassportId->setPlaceholderText("1234-123456");
    ui->lineName->setPlaceholderText("Иванов И.И.");
    ui->linePhone->setPlaceholderText("+79215341289");
}

bool FormCustomer::searchId()
{
       int row_count = model->rowCount();
       QString search = ui->linePassportId->text();
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

void FormCustomer::on_btnOk_clicked()
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
        ui->lblError->setText("Клиент с таким номером паспорта уже есть в системе!");
    }
    else
    {
        emit notifyNewData(processForm());//испускаем сигнал
        this->close();
    }

}
