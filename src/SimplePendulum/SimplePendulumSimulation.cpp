//
// Created by jaehoon on 22. 3. 31.. dkswogns46@gmail.com
//

#include "SimplePendulumSimulation.h"
#include "mainwindow.h"
#include <QApplication>
#include <thread>
#include <cmath>
extern MainWindow *MainUI;

void thread1task(raisim::World *world, SimplePendulumRobot *robot, Controller *controller, double simulationDuration, bool *button1Pressed) {
    double dT = world -> getTimeStep();
    double oneCycleSimTime = 0;
    int divider = ceil(simulationDuration / dT / 200);
    int i = 0;
    int j = 0;
    std::cout<<"divider : "<<divider<<std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        if ((*button1Pressed) && (oneCycleSimTime < simulationDuration)) {
            // simDuration/dT = 1000 / 200 = 5
            i++;
            oneCycleSimTime = i * dT;
            controller->doControl();
            world->integrate();
//            std::cout<<"i : "<<i<<std::endl;
            if(i%divider == 0)
            {
                std::cout<<"j : "<<j<<std::endl;
                MainUI->data_x[j] = world -> getWorldTime();
                MainUI->data_y1[j] = robot -> getQ();
                MainUI->data_y2[j] = robot -> getQD();
                j++;
            }

        }
        else if (i > 100){
            *button1Pressed = false;
            i = 0;
            j = 0;
            oneCycleSimTime = 0;
//            MainUI->plotWidget1();
//            MainUI->plotWidget2();
        }
    }
}

int main(int argc, char *argv[]) {
    std::string urdfPath = "\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_simple_pendulum.urdf";
    std::string name = "cutePendulum";
    raisim::World world;

    double simulationDuration = 1.0;
    SimplePendulumSimulation sim = SimplePendulumSimulation(&world, 0.001);
    SimplePendulumRobot simplePendulum = SimplePendulumRobot(&world, urdfPath, name);
    SimplePendulumPDController PDcontroller = SimplePendulumPDController(&simplePendulum);

    raisim::RaisimServer server(&world);
    server.launchServer(8080);

    QApplication a(argc, argv);
    MainWindow w;
    std::thread thread1(thread1task, &world, &simplePendulum, &PDcontroller, simulationDuration, &w.button1);
    w.show();

    return a.exec();
}

