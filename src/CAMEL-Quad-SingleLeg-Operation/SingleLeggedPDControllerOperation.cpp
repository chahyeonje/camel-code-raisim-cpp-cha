//
// Created by jaehoon on 22. 5. 2.
//

#include "SingleLeggedPDControllerOperation.h"

void SingleLeggedPDControllerOperation::setPDGain(double PGain, double DGain) {
    this->PGain = PGain;
    this->DGain = DGain;
}

void SingleLeggedPDControllerOperation::doControl() {
    updateState();
    computeControlInput();
    setControlInput();
}

void SingleLeggedPDControllerOperation::zeroing() {
    updateState();
    setPDGain(50.0, 2.5);
    double timeDuration = 3.0;
    double dT = 0.001;
    mCubicTrajectoryGen1.updateTrajectory(position[1], 0.785398, 0.0, timeDuration);
    mCubicTrajectoryGen2.updateTrajectory(position[2], -1.570796, 0.0, timeDuration);
    for(int i =0; i < int(timeDuration / dT) ; i++)
    {
        desiredJointPosition << mCubicTrajectoryGen1.getPositionTrajectory(i*dT), mCubicTrajectoryGen2.getPositionTrajectory(i*dT);
        desiredJointVelocity << mCubicTrajectoryGen1.getVelocityTrajectory(i*dT), mCubicTrajectoryGen2.getVelocityTrajectory(i*dT);
        std::cout<<"current position : "<<position<<std::endl;
        std::cout<<"desired position : "<<desiredJointPosition[0] <<" "<<desiredJointPosition[1]<<std::endl;
        doControl();
        usleep(1000);
        mRobot->visualize();
    }
}
void SingleLeggedPDControllerOperation::updateTrajectory() {

}

void SingleLeggedPDControllerOperation::setTrajectory() {
    desiredJointPosition << 0.785398, -1.570796;
    desiredJointVelocity << 0.0, 0.0;
}

void SingleLeggedPDControllerOperation::updateState() {
    position = mRobot->getQ();
    velocity = mRobot->getQD();
}

void SingleLeggedPDControllerOperation::computeControlInput() {
    for (int i = 1; i < 3; i++) {
        positionError[i - 1] = desiredJointPosition[i - 1] - position[i];
        velocityError[i - 1] = desiredJointVelocity[i - 1] - velocity[i];
        torque[i-1] = PGain * positionError[i - 1] + DGain * velocityError[i - 1];
        if(torque[i-1] > mTorqueLimit){torque[i-1] = mTorqueLimit ;}
        else if(torque[i-1] < -mTorqueLimit){torque[i-1] = -mTorqueLimit ;}
    }
}

void SingleLeggedPDControllerOperation::setControlInput() {
    std::cout<<"input torque: "<<torque<<std::endl;
    mRobot->setTorque(torque);
}
