//
// Created by jaehoon on 22. 4. 13..
//

#ifndef RAISIM_RMDX8PROROBOT_H
#define RAISIM_RMDX8PROROBOT_H

#include "../../include/Robot.h"
#include "../../include/CanMotorX8Pro.h"

class RMDX8ProRobot: public Robot{
public:
    RMDX8ProRobot(raisim::World *world, std::string urdfPath, std::string name, CanMotorX8Pro *canMotorX8) : Robot(world, urdfPath, name){
        mCanMotorX8 = canMotorX8;
        mCanMotorX8->turnOnMotor(0x141);
        initialize();
    }
    void initialize() override;
    void setTorque(int motorID, int torque_int);
    double getQ(int motorID);
    double getQD(int motorID);

private:
    CanMotorX8Pro* mCanMotorX8;
};

void RMDX8ProRobot::initialize() {
    Eigen::VectorXd initialJointPosition(robot->getGeneralizedCoordinateDim());
    initialJointPosition.setZero();
    initialJointPosition[0] = getQ(0x141);
    robot->setGeneralizedCoordinate(initialJointPosition);
}

double RMDX8ProRobot::getQ(int motorID){
    // from motor value
    mCanMotorX8->readMultiturnAngularPosition(motorID);
    return mCanMotorX8->getAngularPosition();
}

double RMDX8ProRobot::getQD(int motorID){
    // from motor value
    mCanMotorX8->readMotorStatus2(motorID);
    return mCanMotorX8->getAngularVelocity();
}

void RMDX8ProRobot::setTorque(int motorID, int torque_int) {
    mCanMotorX8->setTorque(motorID, torque_int);
}
#endif //RAISIM_RMDX8PROROBOT_H
