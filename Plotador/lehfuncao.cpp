#include "lehfuncao.h"
#include "ui_lehfuncao.h"

LehFuncao::LehFuncao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LehFuncao)
{
    ui->setupUi(this);
}

LehFuncao::~LehFuncao()
{
    delete ui;
}

void LehFuncao::clear()
{
    ui->lineEdit->clear();
}

void LehFuncao::on_buttonBox_accepted()
{
    emit signDefinirFuncao(ui->lineEdit->text());
}

