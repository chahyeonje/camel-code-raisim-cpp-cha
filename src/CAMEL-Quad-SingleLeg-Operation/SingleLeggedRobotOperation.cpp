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
    getQ();
    getQD();
    robot->setGeneralizedCoordinate(mJointPosition);
    robot->setGeneralizedVelocity(mJointVelocity);
}

Eigen::VectorXd SingleLeggedRobotOperation::getQ() {
    mJointPosition[0] = 0.23 * cos(mJointPosition[1]) + 0.23 * cos(mJointPosition[1] + mJointPosition[2]);
    mJointPosition[1] = mCan->getAngularPosition2() + mHipOffset;
    mJointPosition[2] = mCan->getAngularPosition1() + mKneeOffset;
    return mJointPosition;
}

Eigen::VectorXd SingleLeggedRobotOperation::getQD() {
    mJointVelocity[0] = 0.0;
    mJointVelocity[1] = mCan->getAngularVelocity2();
    mJointVelocity[2] = mCan->getAngularVelocity1();
    return mJointVelocity;
}

double SingleLeggedRobotOperation::getPlot1() {
    return 0;
}

double SingleLeggedRobotOperation::getPlot2() {
    return 0;
}

void SingleLeggedRobotOperation::setTorque(Eigen::VectorXd torque) {
    mCan ->setTorque(mMotorHipID, torque[0]);
    mCan ->setTorque(mMotorKneeID, torque[1]);
}