//
// Created by jaehoon on 22. 3. 31.. dkswogns46@gmail.com
//

#include "SimplePendulumSimulation.h"
#include "mainwindow.h"
#include <QApplication>
#include <thread>


void thread1task(bool *button1Pressed, raisim::World *world, Controller *controller) {
    while (true) {
        if (*button1Pressed) {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            controller->doControl();
            world->integrate();
        }
    }
}

int main(int argc, char *argv[]) {
    std::string urdfPath = "\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_simple_pendulum.urdf";
    std::string name = "cutePendulum";
    raisim::World world;

    SimplePendulumSimulation sim = SimplePendulumSimulation(&world, 0.001);
    SimplePendulumRobot simplePendulum = SimplePendulumRobot(&world, urdfPath, name);
    SimplePendulumPDController PDcontroller = SimplePendulumPDController(&simplePendulum);

    raisim::RaisimServer server(&world);
    server.launchServer(8080);

    QApplication a(argc, argv);
    MainWindow w;
    std::thread thread1(thread1task, &w.button1, &world, &PDcontroller);
    w.show();

    return a.exec();
}

