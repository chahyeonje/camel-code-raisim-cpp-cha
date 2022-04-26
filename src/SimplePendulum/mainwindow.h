//
// Created by jaehoon on 22. 4. 26.
//

#ifndef RAISIM_MAINWINDOW_H
#define RAISIM_MAINWINDOW_H

#include <QMainWindow>
#include "../../include/SimulationThread.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void setSimulation(SimulationThread simThread){this->thread = simThread;}

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void plotWidget1();

    void plotWidget2();
private:
    Ui::MainWindow *ui;
//    SimulationThread thread;
};



#endif //RAISIM_MAINWINDOW_H
