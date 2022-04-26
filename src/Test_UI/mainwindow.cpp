#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::plotWidget1();
    MainWindow::plotWidget2();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotWidget1()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->widget_1->addGraph();
    ui->widget_1->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->widget_1->xAxis->setLabel("x");
    ui->widget_1->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget_1->xAxis->setRange(-1, 1);
    ui->widget_1->yAxis->setRange(0, 1);
    ui->widget_1->replot();
}

void MainWindow::plotWidget2()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->widget_2->xAxis->setLabel("x");
    ui->widget_2->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget_2->xAxis->setRange(-1, 1);
    ui->widget_2->yAxis->setRange(0, 1);
    ui->widget_2->replot();
}
