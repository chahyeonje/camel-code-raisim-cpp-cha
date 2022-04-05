//
// Created by jaehoon on 22. 4. 3..
//

#ifndef RAISIM_SIMPLEPENDULUMPDCONTROLLER_H
#define RAISIM_SIMPLEPENDULUMPDCONTROLLER_H

#include "../../include/Controller.h"

class SimplePendulumPDController : public Controller {
public:
    Eigen::VectorXd torque = Eigen::VectorXd(1);
    double position;
    double velocity;
    double positionError;
    double velocityError;
    double desiredPosition;
    double desiredVelocity;

    double PGain;
    double DGain;

    SimplePendulumPDController(Robot *robot) : Controller(robot) {
        setTrajectory();
        setPDGain(200.0, 25.0);
    }

    void doControl() override;

    void setTrajectory() override;

    void updateState() override;

    void computeControlInput() override;

    void setControlInput() override;

    void setPDGain(double PGain, double DGain);

private:
};

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

#endif //RAISIM_SIMPLEPENDULUMPDCONTROLLER_H
