#ifndef GRAFICO_H
#define GRAFICO_H

#include <QLabel>
#include <string>
#include <evaluator.h>
#include <QPixmap>
#include <QColor>
#include <QResizeEvent>
#include <QMouseEvent>

class Grafico : public QLabel
{
    Q_OBJECT
public:
    Grafico(QWidget *parent = nullptr);
    bool empty();
    void setLimites(int MinX, int MaxX, int MinY, int MaxY, int Expoente);
    void setFuncao(const std::string& S);
    void clearFuncao();
    void setCor(int R, int G, int B);
    void apagar();
    void plotar();

signals:
    void signGraficoClicked(double X, double Y);

private:
    double convXtoJ(double X);
    double convYtoI(double Y);
    double convJtoX(double J);
    double convItoY(double I);
    Evaluator eval;
    QPixmap img;
    QColor cor;
    int largura, altura;
    double minX,maxX,minY,maxY;
    int nMarcX, nMarcY;
    void resizeEvent(QResizeEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // GRAFICO_H
