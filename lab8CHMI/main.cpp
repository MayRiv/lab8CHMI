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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator calculator(0,5);
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
    out.view();
    out.show();
    return a.exec();
}
