#include <QtGui/QApplication>
#include "calculator.h"
#include "test.h"
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <QDialog>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <QLayout>
#include "outputter.h"
#include <math.h>
#include <QFile>
#include <QTextStream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("out.txt");
    file.open( QIODevice::WriteOnly);
    QTextStream outc(&file);                  //erase a trash
    outc << "";
    file.close();
    Calculator  calculator(0,5);
    calculator.calculate();
    freopen("testing.log", "w", stdout);
    QTest::qExec(new Test, argc, argv);

    Outputter out;
    out.addGraph(calculator.getArguments(),calculator.getValues(),1,Qt::red);
    out.addGraph(calculator.getArguments(),calculator.getAccurate(),1,Qt::blue);


    calculator.setNumberOfNodes(20);
    calculator.calculate();
    out.addGraph(calculator.getArguments(),calculator.getValues(),2,Qt::red);
    out.addGraph(calculator.getArguments(),calculator.getAccurate(),2,Qt::blue);

    calculator.setNumberOfNodes(50);
    calculator.calculate();
    out.addGraph(calculator.getArguments(),calculator.getValues(),3,Qt::red);
    out.addGraph(calculator.getArguments(),calculator.getAccurate(),3,Qt::blue);

   // out.addGraph(x,y,40,72,Qt::green);
    QFile in("out.txt");
    in.open(QIODevice::ReadOnly);
    QString something=in.readAll();
    out.printf(something);
    out.view();
    out.show();
    return a.exec();
}
