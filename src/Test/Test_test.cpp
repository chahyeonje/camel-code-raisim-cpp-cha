//
// Created by jaehoon on 22. 6. 27.
//
#include "raisim/World.hpp"
#include "raisim/RaisimServer.hpp"


int main(int argc, char* argv[]) {

    /// create raisim world
    raisim::World world;
    world.setTimeStep(0.001);

    /// create objects
    world.addGround();
    auto robot = world.addArticulatedSystem("\\home\\cha\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_wire_arm\\camel_wire_arm.urdf");

    /// kinova joint PD controller
    Eigen::VectorXd jointNominalConfig(robot->getGeneralizedCoordinateDim()), jointVelocityTarget(robot->getDOF());
    double pi = 3.141592;

    jointVelocityTarget.setZero();
    jointNominalConfig << 0.0;
    robot->setGeneralizedCoordinate(jointNominalConfig);
    robot->setGeneralizedForce(Eigen::VectorXd::Zero(robot->getDOF()));
    robot->setName("robot");

    /// launch raisim server
    raisim::RaisimServer server(&world);
    server.launchServer();
    server.focusOn(robot);
    for (int i=0; i<2000000; i++) {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
//        jointNominalConfig << 0 ;
//        robot->setGeneralizedCoordinate(jointNominalConfig);
        server.integrateWorldThreadSafe();
    }

    server.killServer();
}