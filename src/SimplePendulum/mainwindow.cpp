//
// Created by jaehoon on 22. 4. 26.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//  CAN init
    std::cout<<"button 1 is clicked"<<std::endl;
//    this->thread.Run();
}

void MainWindow::on_pushButton_2_clicked()
{
//  Motor On
    std::cout<<"button 2 is clicked"<<std::endl;
}

void MainWindow::on_pushButton_3_clicked()
{
//  Motor Off
    std::cout<<"button 3 is clicked"<<std::endl;
}

void MainWindow::on_pushButton_4_clicked()
{
//  Start Control
    std::cout<<"button 4 is clicked"<<std::endl;
}

void MainWindow::on_pushButton_5_clicked()
{
//  Stop Control
    std::cout<<"button 5 is clicked"<<std::endl;
}

void MainWindow::on_pushButton_6_clicked()
{
//  Generate New Trajectory
    std::cout<<"button 6 is clicked"<<std::endl;
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
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(-1, 1);
    ui->widget->yAxis->setRange(0, 1);
    ui->widget->replot();
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

