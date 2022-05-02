//
// Created by jaehoon on 22. 4. 3..
//

#ifndef RAISIM_SIMPLEPENDULUMPDCONTROLLER_H
#define RAISIM_SIMPLEPENDULUMPDCONTROLLER_H

#include "include/CAMEL/Controller.h"

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



#endif //RAISIM_SIMPLEPENDULUMPDCONTROLLER_H
