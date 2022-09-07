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
    Eigen::VectorXd torque = Eigen::VectorXd(1);
    double position;
    double velocity;
    double positionError;
    double velocityError;
    double desiredPosition = 0;
    double desiredVelocity = 0;
    double PGain=1;
    double DGain=0.1;

    jointVelocityTarget.setZero();
    jointNominalConfig << pi/3*2;
    robot->setGeneralizedCoordinate(jointNominalConfig);
    robot->setGeneralizedForce(Eigen::VectorXd::Zero(robot->getDOF()));
    robot->setName("robot");

    /// launch raisim server
    raisim::RaisimServer server(&world);
    server.launchServer();
    server.focusOn(robot);
    sleep(3);
    for (int i=0; i<2000000; i++) {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
//        jointNominalConfig << i*180/pi*0.00001 ;
//        robot->setGeneralizedCoordinate(jointNominalConfig);
        position = robot->getGeneralizedCoordinate()[0];
        velocity = robot->getGeneralizedVelocity()[0];
        positionError = desiredPosition - position;
        velocityError = desiredVelocity - velocity;
        torque[0] = PGain * positionError + DGain * velocityError;
        robot->setGeneralizedForce(torque);
        robot->setExternalForce(robot->getBodyIdx("link2"),{0.125,0,0.045},{-5,5,0});
        server.integrateWorldThreadSafe();
    }

    server.killServer();
}