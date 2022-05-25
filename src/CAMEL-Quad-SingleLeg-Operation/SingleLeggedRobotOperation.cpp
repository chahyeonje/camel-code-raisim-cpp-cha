//
// Created by jaehoon on 22. 5. 25.
//

#include "SingleLeggedRobotOperation.h"

void SingleLeggedRobotOperation::initialize() {
    Eigen::VectorXd initialJointPosition(robot->getGeneralizedCoordinateDim());
    initialJointPosition.setZero();
    initialJointPosition[0] = 0.5;  //prismatic joint
    initialJointPosition[1] = 0.0;  //hip
    initialJointPosition[2] = 0.0;  //knee
    robot->setGeneralizedCoordinate(initialJointPosition);
}

void SingleLeggedRobotOperation::visualize() {
    mJointPosition[0] = 0.5;
    mJointPosition[1] = -(mCan->getAngularPosition2() - mHipOffset);
    mJointPosition[2] = -(mCan->getAngularPosition1() - mKneeOffset);
    robot->setGeneralizedCoordinate(mJointPosition);
}
raisim::VecDyn SingleLeggedRobotOperation::getQ(){
    return this->robot->getGeneralizedCoordinate();
}

raisim::VecDyn SingleLeggedRobotOperation::getQD(){
    return this->robot->getGeneralizedVelocity();
}

double SingleLeggedRobotOperation::getPlot1() {
    return 0;
}

double SingleLeggedRobotOperation::getPlot2() {
    return 0;
}