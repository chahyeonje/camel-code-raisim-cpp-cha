//
// Created by jaehoon on 22. 6. 27.
//
#include "raisim/World.hpp"
#include "raisim/RaisimServer.hpp"
#include <vector>
#include <cmath>

Eigen::Matrix2d MassMat(double q1, double q2);

Eigen::Matrix2d CoriloisMat(double q1, double dq1, double q2, double dq2);

Eigen::Vector2d Beta(double q1, double dq1, double q2, double dq2);

int main(int argc, char *argv[]) {

    /// create raisim world
    raisim::World world;
    world.setTimeStep(0.001);

    /// create objects
    world.addGround();
    auto robot = world.addArticulatedSystem(
            "\\home\\cha\\raisimLib\\camel-code-raisim-cpp\\rsc\\test_planar_elbow_2dof_point_mass.urdf");
//    auto robot1 = world.addArticulatedSystem("\\home\\cha\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_wire_arm\\camel_wire_arm1.urdf");
//    auto robot2 = world.addArticulatedSystem("\\home\\cha\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_wire_arm\\camel_wire_arm2.urdf");

    Eigen::VectorXd jointNominalConfig(robot->getGeneralizedCoordinateDim()), jointVelocityTarget(robot->getDOF());
    double pi = 3.141592;
    raisim::VecDyn position = raisim::VecDyn(2);
    raisim::VecDyn velocity = raisim::VecDyn(2);
    Eigen::VectorXd positionError = Eigen::VectorXd(2);
    Eigen::VectorXd velocityError = Eigen::VectorXd(2);
    Eigen::VectorXd desiredPosition = Eigen::VectorXd(2);
    Eigen::VectorXd desiredVelocity = Eigen::VectorXd(2);
    Eigen::VectorXd torque = Eigen::VectorXd(2);
    double PGain = 0.5;
    double DGain = 0.1;

    /// for momentum observer
    Eigen::VectorXd momentum = Eigen::VectorXd(2);
    Eigen::VectorXd momentumPrev = Eigen::VectorXd(2);
    Eigen::VectorXd residual = Eigen::VectorXd(2);
    Eigen::VectorXd beta = Eigen::VectorXd(2);
    Eigen::VectorXd dqMat = Eigen::VectorXd(2);
    Eigen::Matrix2d gainK;
    gainK(0, 0) = 100, gainK(0, 1) = 0;
    gainK(1, 0) = 0, gainK(1, 1) = 100;
    bool firstRun = true;

    jointVelocityTarget.setZero();
    jointNominalConfig << pi/2, pi/6;
    robot->setGeneralizedCoordinate(jointNominalConfig);
    robot->setGeneralizedForce(Eigen::VectorXd::Zero(robot->getDOF()));
    desiredPosition << pi/2, pi/6;
    desiredVelocity << 0, 0;
    robot->setName("robot");

    /// launch raisim server
    raisim::RaisimServer server(&world);
    server.launchServer();
    server.focusOn(robot);
    sleep(3);

    std::cout << "start!!" << std::endl;

    for (int i = 0; i < 2000000; i++) {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        position[0] = robot->getGeneralizedCoordinate()[0];
        position[1] = robot->getGeneralizedCoordinate()[1];
        velocity[0] = robot->getGeneralizedVelocity()[0];
        velocity[1] = robot->getGeneralizedVelocity()[1];
        positionError[0] = desiredPosition[0] - position[0];
        positionError[1] = desiredPosition[1] - position[1];
        velocityError[0] = desiredVelocity[0] - velocity[0];
        velocityError[1] = desiredVelocity[1] - velocity[1];
        beta = Beta(robot->getGeneralizedCoordinate()[0], robot->getGeneralizedVelocity()[0],
                    robot->getGeneralizedCoordinate()[1], robot->getGeneralizedVelocity()[1]);
        torque = PGain * positionError + DGain * velocityError;
        robot->setGeneralizedForce(torque);

        if (i > 1000 && i < 10000) {
            robot->setExternalForce(robot->getBodyIdx("link1"), {0.075, 0, 0}, {1, 0, 0});
        } else {
            robot->setExternalForce(robot->getBodyIdx("link1"), {0.075, 0, 0}, {0, 0, 0});
        }

        server.integrateWorldThreadSafe();
        if (firstRun == true) {
            momentumPrev[0] = 0;
            momentumPrev[1] = 0;
            residual[0] = 0;
            residual[1] = 0;
            firstRun = false;
        }
        dqMat[0] = robot->getGeneralizedVelocity()[0];
        dqMat[1] = robot->getGeneralizedVelocity()[1];

        momentum = momentumPrev + torque * 0.001 - beta * 0.001 + residual * 0.001;
        residual = gainK * (-momentum +
                            MassMat(robot->getGeneralizedCoordinate()[0], robot->getGeneralizedCoordinate()[1]) *
                            dqMat);
        momentumPrev = momentum;

        if(i%100==0){
            std::cout<< i<< ">> " << "joint1: " << residual[0] << "," <<" joint2: "<<residual[1] << ", motor torque : "<< torque[0]<<", "<<torque[1]<<std::endl;
        }
    }
    server.killServer();
}

Eigen::Matrix2d MassMat(double q1, double q2) {
    Eigen::Matrix2d massMat;
    double link1 = 0.1492;  //length of link1
    double link2 = 0.381;   //length of link2
    double mass1 = 0.193;   //mass of link1
    double mass2 = 0.073;   //mass of link2

    massMat(0, 0) = mass1 * link1 * link1 + mass2 * (link1 * link1 + 2 * link1 * link2 * std::cos(q1) + link2 * link2);
    massMat(0, 1) = mass2 * (link2 * link2 + link1 * link2 * std::cos(q2));
    massMat(1, 0) = mass2 * (link2 * link2 + link1 * link2 * std::cos(q2));
    massMat(1, 1) = mass2 * link2 * link2;

    return massMat;
}

Eigen::Matrix2d CoriloisMat(double q1, double dq1, double q2, double dq2) {
    Eigen::Matrix2d coriolisMat;
    double link1 = 0.1492;  //length of link1
    double link2 = 0.381;   //length of link2
    double mass1 = 0.193;   //mass of link1
    double mass2 = 0.073;   //mass of link2

    coriolisMat(0, 0) = -mass2 * link1 * link2 * std::sin(q2) * dq2;
    coriolisMat(0, 1) = -mass2 * link1 * link2 * std::sin(q2) * dq1 - mass2 * link1 * link2 * std::sin(q2) * dq2;
    coriolisMat(1, 0) = -mass2 * link1 * link2 * std::sin(q2) * dq1;
    coriolisMat(1, 1) = 0;

    return coriolisMat;
}

Eigen::Vector2d Beta(double q1, double dq1, double q2, double dq2) {
    Eigen::VectorXd dq2Mat = Eigen::VectorXd(2);
    dq2Mat[0] = dq1;
    dq2Mat[1] = dq2;
    return -CoriloisMat(q1, dq1, q2, dq2).transpose() * dq2Mat;
}
