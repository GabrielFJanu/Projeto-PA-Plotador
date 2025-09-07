#include "mainplotador.h"
#include "ui_mainplotador.h"
#include <QSizePolicy>
#include <QFrame>
#include <QCoreApplication>
#include <QMessageBox>

MainPlotador::MainPlotador(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPlotador)
    , lehFuncao(new LehFuncao(this))
    , grafico(new Grafico(this))
{
    ui->setupUi(this);

    connect(lehFuncao, LehFuncao::signDefinirFuncao, this, MainPlotador::slotDefinirFuncao);
    connect(grafico, Grafico::signGraficoClicked, this, MainPlotador::slotGraficoClicked);

    grafico->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    grafico->setMinimumSize(540,540);
    grafico->setFrameShape(QFrame::Box);
    grafico->setFrameShadow(QFrame::Plain);
    grafico->setAlignment(Qt::AlignCenter);

    grafico->setLimites(ui->spinMinX->value(),ui->spinMaxX->value(),ui->spinMinY->value(),ui->spinMaxY->value(),ui->spinExpoente->value());

    ui->horizontalLayout->insertWidget(0,grafico);

    on_pushApagar_clicked();
}

MainPlotador::~MainPlotador()
{
    delete ui;
}

void MainPlotador::on_actionFun_o_triggered()
{
    lehFuncao->clear();
    lehFuncao->show();
}


void MainPlotador::on_actionPlotar_triggered()
{
    on_pushPlotar_clicked();
}


void MainPlotador::on_actionApagar_triggered()
{
    on_pushApagar_clicked();
}


void MainPlotador::on_actionSair_triggered()
{
    QCoreApplication::quit();
}


void MainPlotador::on_spinMinX_valueChanged(int arg1)
{
    grafico->setLimites(ui->spinMinX->value(),ui->spinMaxX->value(),ui->spinMinY->value(),ui->spinMaxY->value(),ui->spinExpoente->value());

    ui->spinMaxX->setMinimum(1+arg1);

    on_pushApagar_clicked();
}


void MainPlotador::on_spinMaxX_valueChanged(int arg1)
{
    grafico->setLimites(ui->spinMinX->value(),ui->spinMaxX->value(),ui->spinMinY->value(),ui->spinMaxY->value(),ui->spinExpoente->value());

    ui->spinMinX->setMaximum(arg1-1);

    on_pushApagar_clicked();
}


void MainPlotador::on_spinMinY_valueChanged(int arg1)
{
    grafico->setLimites(ui->spinMinX->value(),ui->spinMaxX->value(),ui->spinMinY->value(),ui->spinMaxY->value(),ui->spinExpoente->value());

    ui->spinMaxY->setMinimum(1+arg1);

    on_pushApagar_clicked();
}


void MainPlotador::on_spinMaxY_valueChanged(int arg1)
{
    grafico->setLimites(ui->spinMinX->value(),ui->spinMaxX->value(),ui->spinMinY->value(),ui->spinMaxY->value(),ui->spinExpoente->value());

    ui->spinMinY->setMaximum(arg1-1);

    on_pushApagar_clicked();
}


void MainPlotador::on_spinExpoente_valueChanged(int arg1)
{
    grafico->setLimites(ui->spinMinX->value(),ui->spinMaxX->value(),ui->spinMinY->value(),ui->spinMaxY->value(),ui->spinExpoente->value());

    on_pushApagar_clicked();
}


void MainPlotador::on_radioAzul_clicked()
{
    grafico->setCor(0,0,255);
}


void MainPlotador::on_radioVermelho_clicked()
{
    grafico->setCor(255,0,0);
}


void MainPlotador::on_radioVerde_clicked()
{
    grafico->setCor(0,255,0);
}


void MainPlotador::on_pushPlotar_clicked()
{
    if(grafico->empty()){
        QMessageBox::warning(this,"Funcao indefinida","A funcao a ser plotada nao estah definida");
        return;
    }

    grafico->plotar();
}


void MainPlotador::on_pushApagar_clicked()
{
    grafico->apagar();
}

void MainPlotador::slotDefinirFuncao(QString funcao)
{
    try
    {
        grafico->setFuncao(funcao.toStdString());
        ui->textoFuncao->setPlainText(funcao);
    }
    catch(std::exception &e){
        QMessageBox::critical(this,"Funcao invalida","Erro na funcao: "+QString::fromStdString(e.what()));
        grafico->clearFuncao();
        ui->textoFuncao->clear();
    }
}

void MainPlotador::slotGraficoClicked(double X, double Y)
{
    this->statusBar()->showMessage("X=<"+QString::number(X)+"> Y=<"+QString::number(Y)+">",2000);
}

