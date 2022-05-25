//
// Created by jaehoon on 22. 4. 26.
//

#ifndef RAISIM_SIMULATIONMAINWINDOW_H
#define RAISIM_MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    bool button1 = false;
    bool button2 = false;
    bool button3 = false;
    bool button4 = false;
    bool button5 = false;
    bool button6 = false;
    QVector<double> x;
    QVector<double> y1;
    QVector<double> y2;
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
};



#endif //RAISIM_SIMULATIONMAINWINDOW_H
