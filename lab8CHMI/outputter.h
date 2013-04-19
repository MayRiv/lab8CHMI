#ifndef OUTPUTTER_H
#define OUTPUTTER_H

#include <QDialog>
#include <QVector>
#include <QString>
#include <iostream>
#include <qwt-qt4/qwt_plot.h>
namespace Ui {
class Outputter;
}

class Outputter : public QDialog
{
    Q_OBJECT
    
public:
    explicit Outputter(QWidget *parent = 0);
    ~Outputter();
   // void sum(int x,int y);
    void addGraph(std::pair<QVector<double>,QVector<double> > _graph, int tabNumber,QColor color);
    void addGraph(QVector<double> x,QVector<double>  y,int tabNumber,QColor color);
    void addGraph(double* x, double* y, int numberOfElements, int tabNumber, QColor color);
    void view();
    void printf(QString string);
    //void draw();
    Ui::Outputter *ui;
    QVector<std::pair< std::pair <QVector <double> ,QVector <double> >,std::pair<int,QColor> > > graphs;
    int numberOfTabs;
    QVector<QwtPlot*> plots;

};
#endif // OUTPUTTER_H
