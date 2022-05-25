//
// Created by jaehoon on 22. 5. 2.
//

#include "SingleLeggedRobot.h"

void SingleLegRobot::initialize() {
    Eigen::VectorXd initialJointPosition(robot->getGeneralizedCoordinateDim());
    initialJointPosition.setZero();
    initialJointPosition[0] = 0.5;  //prismatic joint
    initialJointPosition[1] = -60.0 * 3.141592 / 180.0;  //
    initialJointPosition[2] = 120.0 * 3.141592 / 180.0;
    robot->setGeneralizedCoordinate(initialJointPosition);
}

raisim::VecDyn SingleLegRobot::getQ(){
    return this->robot->getGeneralizedCoordinate();
}

raisim::VecDyn SingleLegRobot::getQD(){
    return this->robot->getGeneralizedVelocity();
}

double SingleLegRobot::getPlot1() {
    return 0;
}

double SingleLegRobot::getPlot2() {
    return 0;
}