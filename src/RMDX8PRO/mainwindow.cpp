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
    x = QVector<double>(101);
    y1 = QVector<double>(101);
    y2 = QVector<double>(101);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//  CAN init
    std::cout<<"'CAN init' button is clicked"<<std::endl;
//    plotWidget1();
//    plotWidget2();
    if(button1){button1 = false;}
    else{button1 = true;}
}

void MainWindow::on_pushButton_2_clicked()
{
//  Raisim init
    std::cout<<"'Raisim init' button is clicked"<<std::endl;
    if(button2){button2 = false;}
    else{button2 = true;}
}

void MainWindow::on_pushButton_3_clicked()
{
//  Motor On
    std::cout<<"'Motor On' button is clicked"<<std::endl;
    if(button3){button3 = false;}
    else{button3 = true;}
}

void MainWindow::on_pushButton_4_clicked()
{
//  Motor Off
    std::cout<<"'Motor Off' button is clicked"<<std::endl;
    if(button4){button4 = false;}
    else{button4 = true;}
}

void MainWindow::on_pushButton_5_clicked()
{
//  Start Control
    std::cout<<"'Start' button is clicked"<<std::endl;
    if(button5){button5 = false;}
    else{button5 = true;}
}

void MainWindow::on_pushButton_6_clicked()
{
//  Generate New Trajectory
    std::cout<<"'Generate New Trajectory button' is clicked"<<std::endl;
    if(button6){button6 = false;}
    else{button6 = true;}
}

void MainWindow::plotWidget1()
{
    // generate some data:
    for (int i=0; i<101; ++i)
    {
        x[i] = i/10.0; // x goes from -1 to 1
        y1[i] = x[i] * x[i];
    }
    // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y1);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y1");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(-1, 10);
    ui->widget->yAxis->setRange(0, 1);
    ui->widget->replot();
}

void MainWindow::plotWidget2()
{

    // generate some data:
     // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/10.0; // x goes from -1 to 1
        y2[i] = x[i] * x[i];
    }
    // create graph and assign data to it:
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setData(x, y2);
    // give the axes some labels:
    ui->widget_2->xAxis->setLabel("x");
    ui->widget_2->yAxis->setLabel("y2");
    // set axes ranges, so we see all data:
    ui->widget_2->xAxis->setRange(-1, 10);
    ui->widget_2->yAxis->setRange(0, 1);
    ui->widget_2->replot();
}

