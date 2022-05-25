//
// Created by jaehoon on 22. 5. 2.
//

#include "SingleLeggedPDController.h"

void SingleLegPDController::setPDGain(double PGain, double DGain) {
    this->PGain = PGain;
    this->DGain = DGain;
}

void SingleLegPDController::doControl() {
    updateState();
    computeControlInput();
    setControlInput();
}

void SingleLegPDController::setTrajectory() {
    desiredPosition = 0.45;
    desiredVelocity = 0.0;
}

void SingleLegPDController::updateState() {
    position = getRobot()->robot->getGeneralizedCoordinate();
    velocity = getRobot()->robot->getGeneralizedVelocity();
}

void SingleLegPDController::computeControlInput() {
    for(int i = 1; i<3 ; i++)
    {
        positionError[i-1] = desiredJointPosition[i-1] - position[i];
        velocityError[i-1] = desiredJointVelocity[i-1] - velocity[i];
        torque[i] = PGain * positionError[i-1] + DGain * velocityError[i-1];
    }
}

void SingleLegPDController::setControlInput() {
    getRobot()->robot->setGeneralizedForce(torque);
}
