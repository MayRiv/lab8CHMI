#include "calculator.h"
#include "ui_calculator.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include <QFile>
using namespace std;
/*Calculator::Calculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calculator)
{
    a=1.0/400;
    n=5;
    ui->setupUi(this);
}*/
Calculator::Calculator(QWidget *parent,int _n):
    QDialog(parent),ui(new Ui::Calculator)
{
    a=1.0/400;
    n=_n;
    ui->setupUi(this);

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::calculate()
{
    double h=(1.0-0.0)/(n+1);
    QVector<double> x(n);
    x[0]=0+h;
    for (int i=1;i<x.size();i++) x[i]+=x[i-1]+h;
    QVector<double> C=getC(x);
    h=(1.0-0.0)/(4*n+1);
    double argument=0;
    QFile file("out.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);


    for (int i=0;i<4*n+1+1;i++)
    {

        double yApproximate=0;
        for (int i=0;i<C.size();i++) yApproximate+=C[i]*baseFunction(i+1,argument);
        //printf("%lf yApp=%lf  yAcc=%lf\n",(yApproximate-getAccurateValue(argument))/(yApproximate)*100,yApproximate,getAccurateValue(argument));
        //std::cout << "xyy";
        out <<"x= "<< argument<<" yt ="<< getAccurateValue(argument)<<" yp= "<<yApproximate<<" abs= "<<getAccurateValue(argument)-yApproximate<<" otn"<<(getAccurateValue(argument)-yApproximate)/yApproximate*100 <<"\n";
        qDebug()<<"x= "<< argument<<"yt ="<< getAccurateValue(argument)<<"yp= "<<yApproximate<<"abs= "<<getAccurateValue(argument)-yApproximate<<"otn"<<(getAccurateValue(argument)-yApproximate)/yApproximate*100;
        arguments.push_back(argument);
        values.push_back(yApproximate);
        accurate.push_back(getAccurateValue(argument));
        argument+=h;
    }
    double yApproximate=0;
    for (int i=0;i<C.size();i++) yApproximate+=C[i]*baseFunction(i+1,0.5);

    qDebug()<<"pri x=0.5 "<<"yt ="<< getAccurateValue(0.5)<<"yp= "<<yApproximate<<"abs= "<<getAccurateValue(0.5)-yApproximate<<"otn"<<(getAccurateValue(0.5)-yApproximate)/yApproximate*100;
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    out << "     \n\n\n";
    file.close();
}

double Calculator::baseFunction(int j, double x)
{
    return sin(j*M_PI*x);
}

double Calculator::derrivateBaseFunction(int j, double x)
{
    return j*M_PI*cos(j*M_PI*x);
}

double Calculator::doubleDerrivateBaseFunction(int j, double x)
{
    return -pow(j*M_PI,2.0)*sin(j*M_PI*x);
}

double Calculator::r(double x)
{
    return a;
}

double Calculator::p(double x)
{
    return 0;
}

double Calculator::q(double x)
{
    return -1;
}

double Calculator::rightPartFunction(double x)
{
    return pow(cos(M_PI*x),2)+2*a*M_PI*M_PI*cos(2*M_PI*x);
}

double* Calculator::methodGauss02(const double* pA,	const double* pB,	int n )
{
    static const char* methodGauss02 = "methodGauss02!";
    static const char* nullPointer = "Null-pointer!";
    static const char* noMemory = "No-memory!";
    static const char* nEquals0 = "n = 0!";

    double* X = NULL;

    if(!pA || !pB)
        printf("\n%s: %s\n", methodGauss02, nullPointer);
    else if(!n)
        printf("\n%s: %s\n", methodGauss02, nEquals0);
    else
    {
        double** A = NULL;	//A[0] -> A[0][0]
        double* B = NULL;	//
        int* ci = NULL;	//current row indexes
        int* cj = NULL; //current column indexes

        if(!(A = (double**)malloc(sizeof(double*)*n)) ||
             !(B = (double*)malloc(sizeof(double)*n)) ||
             !(ci = (int*)malloc(sizeof(int)*n)) ||
             !(cj = (int*)malloc(sizeof(int)*n)) ||
             !(A[0] = (double*)malloc(sizeof(double)*n*n))
             )
             printf("\n%s: %s\n", methodGauss02, noMemory);
        else
        {
            if(!(X = (double*)malloc(sizeof(double)*n)))
                printf("\n%s: %s\n", methodGauss02, noMemory);
            else
            {
                int i;	//row index
                int j;	//column index
                int k;	//row index
                int imax;	//row index of maximum element
                int jmax;	//colon index of maximum element
                int temp;
                double R;	//R = A[i+1][i] / A[i][i]
                double S;	//Si = A[i][i+1] * X[i+1] + A[i][i+2] * X[i+2] -...

                for(i = 1; i < n; i++)
                    A[i] = &A[0][i*n];

                for(i = 0; i < n; i++)
                {
                    ci[i] = i;
                    cj[i] = i;
                }

                //Copying pA to A and B to B
                for(i = 0; i < n*n; i++)
                    A[0][i] = pA[i];
                for(i = 0; i < n; i++)
                    B[i] = pB[i];

                //Making A triangle
                for(i = 0; i < n-1; i++)
                {
                    //Seeking for maximum element
                    imax = i;
                    jmax = i;
                    for(k = i; k < n; k++)
                        for(j = i; j < n; j++)
                            if(fabs(A[ci[k]][cj[j]]) > fabs(A[ci[imax]][cj[jmax]]))
                            {
                                imax = k;
                                jmax = j;
                            }

                    //if imax != i then exchanging A[i] and A[imax] rows
                    if(imax != i)
                    {
                        temp = ci[i];
                        ci[i] = ci[imax];
                        ci[imax] = temp;
                    }
                    if(jmax != i)
                    {
                        temp = cj[i];
                        cj[i] = cj[jmax];
                        cj[jmax] = temp;
                    }

                    //Making 0s in i column from i+1 row to n-1 row
                    for(k = i+1; k < n; k++)
                    {
                        R = A[ci[k]][cj[i]] / A[ci[i]][cj[i]];

                        // for(j = i+1!!!...)
                        for(j = i; j < n; j++)
                            A[ci[k]][cj[j]] = A[ci[k]][cj[j]] - R * A[ci[i]][cj[j]];
                        B[ci[k]] = B[ci[k]] - R * B[ci[i]];
                    }
                }

                //Calculating X
                B[ci[n-1]] = B[ci[n-1]] / A[ci[n-1]][cj[n-1]];
                for(k = n-2; k >= 0; k--)
                {
                    S = 0;
                    for(j = k+1; j < n; j++)
                        S = S + A[ci[k]][cj[j]] * B[ci[j]];
                    B[ci[k]] = (B[ci[k]] - S) / A[ci[k]][cj[k]];
                }

                for(i = 0; i < n; i++)
                    X[cj[i]] = B[ci[i]];
            }
            free(A[0]);
        }

        free(A);
        free(B);
        free(ci);
        free(cj);
    }
    double XTest[n];
    QVector<double> XTestVector(n);
    for (int i=0;i<n;i++) XTestVector[i]=X[i];
    return X;
}
QVector<double> Calculator::solveGauss(QVector<double> A, QVector<double> B)//Векторная обёртка над массивным гауссом.
{
   double* pA=new double [A.size()];
   double* pB=new double [B.size()];
   for (int i=0;i<A.size();i++) pA[i]=A[i];
   for (int i=0;i<B.size();i++) pB[i]=B[i];
   double* pX=new double [B.size()];
   pX=methodGauss02(pA,pB,B.size());
   QVector<double> result(B.size());
   for (int i=0;i<B.size();i++) result[i]=pX[i];
   delete pA;
   delete pB;
   delete pX;
   return result;

}
QVector<double> Calculator::getC(QVector<double> x)
{
    QVector<double> A(x.size()*x.size());
    QVector<double> B(x.size());
    for (int i=0;i<x.size();i++)
        for (int j=0;j<x.size();j++)
            A[i*x.size()+j]=r(x[i])*doubleDerrivateBaseFunction(j+1,x[i])+p(x[i])*derrivateBaseFunction(j+1,x[i])+q(x[i])*baseFunction(j+1,x[i]);
    /*A[0]=0.227222;
    A[1]=0.072407;
    A[2]=0.227200;
    A[3]=0.153148;*/

    for (int i=0;i<x.size();i++) B[i]=rightPartFunction(x[i]);
    QVector<double> C= solveGauss(A,B);
    foreach(double coeff, C)
    {
        qDebug() << coeff;
    }
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    return C;
}
double Calculator::getAccurateValue(double x)
{
    return (exp((x-1)/sqrt(a))+exp(-x/sqrt(a)))/(1+exp(-1/sqrt(a)))-pow(cos(M_PI*x),2);
}
 void Calculator::setNumberOfNodes(int _n)
{
    n=_n;
    arguments.clear();
    values.clear();
    accurate.clear();
}
