#include "outputter.h"
#include "ui_outputter.h"
#include <QLineEdit>
#include <qwt-qt4/qwt_plot.h>
#include <QLayout>
#include <QPen>
#include <qwt-qt4/qwt_plot_curve.h>
Outputter::Outputter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Outputter)
{
    numberOfTabs=0;
    ui->setupUi(this);
}

Outputter::~Outputter()
{
    delete ui;
}
void Outputter::addGraph(std::pair<QVector<double>,QVector<double> > _graph,int tabNumber,QColor color)
{

    graphs.push_back(std::pair< std::pair <QVector <double> ,QVector <double> >,std::pair<int,QColor> >(_graph,std::pair<int,QColor> (tabNumber,color)));
}
void Outputter::addGraph(QVector<double> x,QVector<double>  y,int tabNumber, QColor color)
{   
    if (tabNumber>numberOfTabs+1) tabNumber=numberOfTabs+1;
    if (tabNumber<1) tabNumber=1;
    graphs.push_back(std::pair< std::pair <QVector <double> ,QVector <double> >,std::pair<int,QColor> >(std::pair<QVector<double>,QVector<double> > (x,y),std::pair<int,QColor> (tabNumber,color)));
    if (tabNumber>numberOfTabs)
    {
      QwtPlot *plot=new QwtPlot;
      plots.push_back(plot);
      ui->tabWidget->addTab(plots.back(),"Graph");
      numberOfTabs++;
    }
}
void Outputter::addGraph(double* x, double* y, int numberOfElements, int tabNumber, QColor color)
{
    QVector<double> xMas(numberOfElements);

    QVector<double> yMas(numberOfElements);

    for (int i=0;i<numberOfElements;i++)
    {
        xMas[i]=x[i];
        yMas[i]=y[i];
    }
    addGraph(xMas,yMas,tabNumber,color);
}
void Outputter::printf(QString string)
{
    ui->plainTextEdit->setPlainText(string);
}

void Outputter::view()
{
    QVector<QwtPlotCurve*> functions(graphs.size());
    //QwtPlotCurve** functions=new  QwtPlotCurve* [graphs.size()];

    for (int i=0;i<graphs.size();i++)
    {
        functions[i]=new QwtPlotCurve;
        functions[i]->setRenderHint(QwtPlotItem::RenderAntialiased);
        QPen pen(graphs[i].second.second);
        functions[i]->setPen(pen);
        functions[i]->setData(graphs[i].first.first,graphs[i].first.second);
        functions[i]->attach(plots[graphs[i].second.first-1]);
    }

    foreach(QwtPlot* plot,plots)
    {
        plot->replot();
    }

}

