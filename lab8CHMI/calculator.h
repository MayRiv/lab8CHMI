#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QVector>
namespace Ui {
class Calculator;
}

class Calculator : public QDialog
{
    Q_OBJECT
    friend class Test;
public:
   //explicit Calculator(QWidget *parent = 0);
    explicit Calculator(QWidget *parent=0,int _n=20);
    ~Calculator();
    void calculate();
    QVector<double> getValues(){return values;}
    QVector<double> getArguments(){return arguments;}
    QVector<double> getAccurate(){return accurate;}
    void setNumberOfNodes(int _n);
private:
    double baseFunction(int j, double x);
    double derrivateBaseFunction(int j, double x);
    double doubleDerrivateBaseFunction(int j, double x);
    double r(double x);
    double p(double x);
    double q(double x);
    double rightPartFunction(double x);
    double*methodGauss02(const double* pA,const double* pB,int n);
    double getAccurateValue(double x);
    double derrivate(double (*f)(int,double),int j, double x);
    QVector<double> getC(QVector<double> x);
    QVector<double> solveGauss(QVector<double> A, QVector<double> B);
    Ui::Calculator *ui;
    QVector<double> arguments;
    QVector<double> values;
    QVector<double> accurate;
    double a;
    int n;
};

#endif // CALCULATOR_H
