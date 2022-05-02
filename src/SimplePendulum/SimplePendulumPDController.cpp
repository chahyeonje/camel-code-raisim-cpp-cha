//
// Created by jaehoon on 22. 5. 2.
//

#include "SimplePendulumPDController.h"

void SimplePendulumPDController::setPDGain(double PGain, double DGain) {
    this->PGain = PGain;
    this->DGain = DGain;
}

void SimplePendulumPDController::doControl() {
    updateState();
    computeControlInput();
    setControlInput();
}

void SimplePendulumPDController::setTrajectory() {
    desiredPosition = -1.57;
    desiredVelocity = 0.0;;
}

void SimplePendulumPDController::updateState() {
    position = getRobot()->robot->getGeneralizedCoordinate()[0];
    velocity = getRobot()->robot->getGeneralizedVelocity()[0];
}

void SimplePendulumPDController::computeControlInput() {
    positionError = desiredPosition - position;
    velocityError = desiredVelocity - velocity;
    torque[0] = PGain * positionError + DGain * velocityError;
}

void SimplePendulumPDController::setControlInput() {
    getRobot()->robot->setGeneralizedForce(torque);
}
