#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_1_clicked()
{
    // CAN Init
    if (buttonCANInit) { buttonCANInit = false; }
    else { buttonCANInit = true; }
    std::cout<<"CAN Init button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_2_clicked()
{
    // Raisim Init
    if (buttonRaisimInit) { buttonRaisimInit = false; }
    else { buttonRaisimInit = true; }
    std::cout<<"Raisim Init button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_3_clicked()
{
    // Motor On
    if (buttonMotorOn) { buttonMotorOn = false; }
    else { buttonMotorOn = true; }
    std::cout<<"Motor On button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_4_clicked()
{
    // Motor Off
    if (buttonMotorOff) { buttonMotorOff = false; }
    else { buttonMotorOff = true; }
    std::cout<<"Motor Off button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_5_clicked()
{
    // Start Control
    if (buttonStartControl) { buttonStartControl = false; }
    else { buttonStartControl = true; }
    std::cout<<"Start Control button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_6_clicked()
{
    // Stop Control
    if (buttonStopControl) { buttonStopControl = false; }
    else { buttonStopControl = true; }
    std::cout<<"Stop Control button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_7_clicked()
{
    // Generate new cubic trajectory
    if (buttonGenerateCubicTrajectory) { buttonGenerateCubicTrajectory = false; }
    else { buttonGenerateCubicTrajectory = true; }
    std::cout<<"Generate Cubic Trajectory button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_8_clicked()
{
    // Generate new sin trajectory
    if (buttonGenerateSinTrajectory) { buttonGenerateSinTrajectory = false; }
    else { buttonGenerateSinTrajectory = true; }
    std::cout<<"Generate Sin Trajectory button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_9_clicked()
{
    // Jump
    if (buttonJump) { buttonJump = false; }
    else { buttonJump = true; }
    std::cout<<"Jump button is clicked."<<std::endl;
}

void MainWindow::on_pushButton_10_clicked()
{
    if (buttonZeroing) { buttonZeroing = false; }
    else { buttonZeroing = true; }
    std::cout<<"Zeroing button is clicked."<<std::endl;
}
