//
// Created by jaehoon on 22. 4. 13..
//

#ifndef RAISIM_RMDX8PROPDCONTROLLER_H
#define RAISIM_RMDX8PROPDCONTROLLER_H

#include "RMDX8ProRobot.h"

class RMDX8ProPDContorller {
public:
    double torque;
    double torqueLimit = 10; //integer value
    double position;
    double velocity;
    double positionError;
    double velocityError;
    double desiredPosition;
    double desiredVelocity;

    double PGain;
    double DGain;

    RMDX8ProPDContorller(RMDX8ProRobot *robot) {

        mRobot = robot;
        setPDGain(100.0, 5.0);
    }

    void doControl();

    void setTrajectory(double desPosition, double desVelocity);

    void updateState();

    void computeControlInput();

    void setControlInput();

    void setPDGain(double PGain, double DGain);

    bool isTerminateCondition();

private:
    RMDX8ProRobot *mRobot;

};

void RMDX8ProPDContorller::setPDGain(double PGain, double DGain) {
    this->PGain = PGain;
    this->DGain = DGain;
}

void RMDX8ProPDContorller::doControl() {
    updateState();
    computeControlInput();
    setControlInput();
}

void RMDX8ProPDContorller::setTrajectory(double desPosition, double desVelocity) {
    desiredPosition = desPosition;
    desiredVelocity = desVelocity;
}

void RMDX8ProPDContorller::updateState() {
    position = mRobot->getQ(0x141);
    velocity = mRobot->getQD(0x141);
    Eigen::VectorXd jointPosition(mRobot->robot->getGeneralizedCoordinateDim());
    jointPosition.setZero();
    jointPosition[0] = position;
    mRobot->robot->setGeneralizedCoordinate(jointPosition);
}

void RMDX8ProPDContorller::computeControlInput() {
    positionError = desiredPosition - position;
    velocityError = desiredVelocity - velocity;
    torque = PGain * positionError + DGain * velocityError;

}

void RMDX8ProPDContorller::setControlInput() {
    if (torque > torqueLimit) {
        torque = torqueLimit;
    } else if (torque < -torqueLimit) {
        torque = -torqueLimit;
    }
    mRobot->setTorque(0x141, torque);
    std::cout << "torque : " << torque << std::endl;
}

bool RMDX8ProPDContorller::isTerminateCondition() {
    if (abs(positionError) < 0.01) {
        return true;
    }
}

#endif //RAISIM_RMDX8PROPDCONTROLLER_H
