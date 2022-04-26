//
// Created by jaehoon on 22. 3. 31.. dkswogns46@gmail.com
//

#include "SimplePendulumSimulation.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    std::string urdfPath = "\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_simple_pendulum.urdf";
    std::string name = "cutePendulum";
    raisim::World world;

    SimplePendulumSimulation sim = SimplePendulumSimulation(&world, 0.001);
    SimplePendulumRobot simplePendulum = SimplePendulumRobot(&world, urdfPath, name);
    SimplePendulumPDController PDcontroller = SimplePendulumPDController(&simplePendulum);

    raisim::RaisimServer server(&world);
    server.launchServer(8080);

    SimulationThread thread(&world, &PDcontroller);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
