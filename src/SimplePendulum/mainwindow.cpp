//
// Created by jaehoon on 22. 4. 26.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow *MainUI;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    MainUI = this;
    ui->setupUi(this);
    for (int i=0; i<200; ++i)
    {
        data_x[i] = 0;
        data_y1[i] = 0;
        data_y2[i] = 0;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::cout<<"'Run' button is clicked"<<std::endl;
    if(button1){button1 = false;}
    else{button1 = true;}
}

void MainWindow::plotWidget1()
{
    QVector<double> x(200);
    QVector<double> y1(200);
    for (int i=0; i<200; ++i)
    {
        x[i] = data_x[i];
        y1[i] = data_y1[i];
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y1);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("time [sec]");
    ui->widget->yAxis->setLabel("position");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(x[0], x[199]+ 0.001);
    ui->widget->yAxis->setRange(-2, 2);
    ui->widget->replot();
}

void MainWindow::plotWidget2()
{
    QVector<double> x(200);
    QVector<double> y2(200);
    for (int i=0; i<200; ++i)
    {
        x[i] = data_x[i];
        y2[i] = data_y2[i];
    }
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setData(x, y2);
    // give the axes some labels:
    ui->widget_2->xAxis->setLabel("time [sec]");
    ui->widget_2->yAxis->setLabel("velocity");
    // set axes ranges, so we see all data:
    ui->widget_2->xAxis->setRange(x[0], x[199]+0.001);
    ui->widget_2->yAxis->setRange(-10, 5);
    ui->widget_2->replot();
}

