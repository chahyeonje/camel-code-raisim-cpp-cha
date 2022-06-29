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
    auto robot = world.addArticulatedSystem("\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_wire_arm\\camel_wire_arm.urdf");
    auto robot1 = world.addArticulatedSystem("\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_wire_arm\\camel_wire_arm1.urdf");
    auto robot2 = world.addArticulatedSystem("\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_wire_arm\\camel_wire_arm2.urdf");

    /// kinova joint PD controller
    Eigen::VectorXd jointNominalConfig(robot->getGeneralizedCoordinateDim()), jointVelocityTarget(robot->getDOF());
    double pi = 3.141592;

    jointVelocityTarget.setZero();
    jointNominalConfig << 0.0;
    robot->setGeneralizedCoordinate(jointNominalConfig);
    robot->setGeneralizedForce(Eigen::VectorXd::Zero(robot->getDOF()));
    robot->setName("robot");

    jointNominalConfig << pi/2.0;
    robot1->setGeneralizedCoordinate(jointNominalConfig);
    robot1->setGeneralizedForce(Eigen::VectorXd::Zero(robot->getDOF()));
    robot1->setName("robot1");

    jointNominalConfig << pi/1.5;
    robot2->setGeneralizedCoordinate(jointNominalConfig);
    robot2->setGeneralizedForce(Eigen::VectorXd::Zero(robot->getDOF()));
    robot2->setName("robot2");
    /// launch raisim server
    raisim::RaisimServer server(&world);
    server.launchServer();
    server.focusOn(robot);
    for (int i=0; i<2000000; i++) {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        jointNominalConfig << pi / 2.0 - (double)i/20000;
        robot->setGeneralizedCoordinate(jointNominalConfig);
        server.integrateWorldThreadSafe();
    }

    server.killServer();
}