#include "grafico.h"
#include <QPen>
#include <QPainter>
#include <QLineF>

Grafico::Grafico(QWidget *parent)
    : QLabel(parent)
    , eval()
    , img()
    , cor(0,0,255)
    , largura(0)
    , altura(0)
    , minX(0.0)
    , maxX(0.0)
    , minY(0.0)
    , maxY(0.0)
    , nMarcX(0)
    , nMarcY(0)
{

}

bool Grafico::empty()
{
    return eval.empty();
}

void Grafico::setLimites(int MinX, int MaxX, int MinY, int MaxY, int Expoente)
{
    minX = MinX * pow(10.0, Expoente);
    maxX = MaxX * pow(10.0, Expoente);
    minY = MinY * pow(10.0, Expoente);
    maxY = MaxY * pow(10.0, Expoente);

    nMarcX = 1+MaxX-MinX;
    nMarcY = 1+MaxY-MinY;
}

void Grafico::setFuncao(const std::string &S)
{
    eval.set(S);
}

void Grafico::clearFuncao()
{
    eval.clear();
}

void Grafico::setCor(int R, int G, int B)
{
    cor = QColor(R,G,B);
}

void Grafico::apagar()
{
    largura = this->width();
    altura = this->height();

    img = QPixmap(largura,altura);

    img.fill(Qt::white);

    QPen pen(Qt::black);
    QPainter painter(&img);
    pen.setWidth(3);
    painter.setPen(pen);

    double Izero = convYtoI(0.0), Jmarc;
    if(Izero>=0.0 && Izero<=altura-1){
        painter.drawLine(QLineF(0.0,Izero,largura-1,Izero));
        for(int i = 0; i < nMarcX; i++){
            Jmarc = convXtoJ(minX + (maxX-minX)*i/(nMarcX-1));
            painter.drawLine(QLineF(Jmarc,Izero-3,Jmarc,Izero+3));
        }
    }

    double Jzero = convXtoJ(0.0), Imarc;
    if(Jzero>=0.0 && Jzero<=largura-1){
        painter.drawLine(QLineF(Jzero,0.0,Jzero,altura-1));
        for(int i = 0; i < nMarcY; i++){
            Imarc = convYtoI(minY + (maxY-minY)*i/(nMarcY-1));
            painter.drawLine(QLineF(Jzero-3,Imarc,Jzero+3,Imarc));
        }
    }

    this->setPixmap(img);
}

void Grafico::plotar()
{
    QPen pen(cor);
    QPainter painter(&img);
    pen.setWidth(1);
    painter.setPen(pen);

    double Iant(-1), X, Y, I;
    for(int J = 0; J < largura; J++){
        X = convJtoX(J);
        Y = eval(X);
        I = convYtoI(Y);
        if(I>=0.0 && I<=(altura-1) && Iant>=0.0 && Iant<=(altura-1)){painter.drawLine(QLineF(J-1,Iant,J,I));}
        Iant = I;
    }
    this->setPixmap(img);
}

double Grafico::convXtoJ(double X)
{
    return (largura-1)*(X-minX)/(maxX-minX);
}

double Grafico::convYtoI(double Y)
{
    return (altura-1)*(maxY-Y)/(maxY-minY);
}

double Grafico::convJtoX(double J)
{
    return minX+(maxX-minX)*J/(largura-1);
}

double Grafico::convItoY(double I)
{
    return maxY-(maxY-minY)*I/(altura-1);
}

void Grafico::resizeEvent(QResizeEvent *event)
{
    if(event->size() != event->oldSize()){
        this->apagar();
        if(!(this->empty())){this->plotar();}
    }
}

void Grafico::mouseReleaseEvent(QMouseEvent *event)
{
    emit signGraficoClicked(convJtoX(event->position().x()),convItoY(event->position().y()));
}
