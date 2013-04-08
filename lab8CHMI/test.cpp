#include "test.h"
#include <QTest>
#include <QVector>
//#include <QtTest/QTest>
#include "calculator.h"
#include <math.h>
Test::Test(QObject *parent) :
    QObject(parent)
{
}
void Test::baseFunction()
{
    Calculator calculator;
    //QCOMPARE(calculator.baseFunction(1,0),0);
    //QCOMPARE(calculator.baseFunction(1,0),0);
    QTest::qCompare(fabs(calculator.baseFunction(1,0)-0.0)<0.0000001,true,"sin(2,1)","0","test.h",15);
    QTest::qCompare(fabs(calculator.baseFunction(2,1)-0.0)<0.0000001,true,"sin(2,1)","0","test.h",16);

}

void Test::solveGauss()
{
    Calculator calculator;
    QVector<double> A(4);
    A[0]=7;
    A[1]=1;
    A[2]=6;
    A[3]=8;
    QVector<double> B(2);
    B[0]=3;
    B[1]=6;
    QVector<double> X(2);
    X[0]=0.36;
    X[1]=0.48;
    //QTest::qCompare(calculator.solveGauss(A,B),X,"testing gauss","true","test.h",35);
    QTest::qCompare(fabs(calculator.solveGauss(A,B)[0]-X[0])<0.0001,true,"s","s","s",36);
    QTest::qCompare(fabs(calculator.solveGauss(A,B)[1]-X[1])<0.0001,true,"s","s","s",36);
    //A[]
}

void Test::derrivateBaseFunction()
{
    Calculator calculator;
    double derrivate= (calculator.baseFunction(3,3+0.00001)-calculator.baseFunction(3,3))/0.00001;
    QTest::qCompare(fabs(derrivate-calculator.derrivateBaseFunction(3,3))<0.001,true,"true","true","test.h",45);
}

void Test::doubleDerrivateBaseFunction()
{
    Calculator calculator;
    double derrivate= (calculator.derrivateBaseFunction(3,1.3+0.001)-calculator.derrivateBaseFunction(3,1.3))/0.001;
    QTest::qCompare(fabs(derrivate-calculator.doubleDerrivateBaseFunction(3,1.3))<0.001,true,"true","true","test.h",45);
}
