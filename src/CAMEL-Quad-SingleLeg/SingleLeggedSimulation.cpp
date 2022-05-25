//
// Created by jaehoon on 22. 3. 31.. dkswogns46@gmail.com
//

#include "SingleLeggedSimulation.h"
#include "include/SimulationUI/simulationMainwindow.h"
#include <QApplication>
#include <thread>
#include <cmath>
extern MainWindow *MainUI;
bool timeChecker = false;

void thread1task(raisim::World *world, SingleLegRobot *robot, Controller *controller, double simulationDuration) {
    double dT = world -> getTimeStep();
    double oneCycleSimTime = 0;
    int divider = ceil(simulationDuration / dT / 200);
    int i = 0;
    while (true) {
        if(timeChecker) {
            if ((MainUI->button1) && (oneCycleSimTime < simulationDuration)) {
                oneCycleSimTime = i * dT;
                controller->doControl();
                world->integrate();
                if (i % divider == 0) {
                    MainUI->data_x[MainUI->data_idx] = world->getWorldTime();
                    MainUI->data_y1[MainUI->data_idx] = robot->getPlot1();
                    MainUI->data_y2[MainUI->data_idx] = robot->getPlot2();
                    MainUI->data_idx += 1;
                }
                i++;
                timeChecker = false;
            } else if (oneCycleSimTime >= simulationDuration) {
                MainUI->button1 = false;
                i = 0;
                oneCycleSimTime = 0;
                MainUI->plotWidget1();
                MainUI->plotWidget2();
                MainUI->data_idx = 0;
            }
        }
    }
}

void thread2task()
{
    while(true)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            timeChecker = true;
        }
}

int main(int argc, char *argv[]) {
    std::string urdfPath = "\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_single_leg\\camel_single_leg.urdf";
    std::string name = "single_leg";
    raisim::World world;

    double simulationDuration = 10.0;
    SingleLeggedSimulation sim = SingleLeggedSimulation(&world, 0.001);
    SingleLegRobot singleLeg= SingleLegRobot(&world, urdfPath, name);
    SingleLegPDController PDcontroller = SingleLegPDController(&singleLeg);

    raisim::RaisimServer server(&world);
    server.launchServer(8080);

    QApplication a(argc, argv);
    MainWindow w;
    std::thread thread1(thread1task, &world, &singleLeg, &PDcontroller, simulationDuration);
    std::thread thread2(thread2task);
    w.show();

    return a.exec();
}

