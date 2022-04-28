//
// Created by jaehoon on 22. 4. 26.
//

#ifndef RAISIM_MAINWINDOW_H
#define RAISIM_MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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
    bool button1 = false;
    double data_x[200];
    double data_y1[200];
    double data_y2[200];

public slots:
    void plotWidget1();
    void plotWidget2();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif //RAISIM_MAINWINDOW_H
