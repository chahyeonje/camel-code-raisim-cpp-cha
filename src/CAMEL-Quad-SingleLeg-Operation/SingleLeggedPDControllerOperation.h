//
// Created by jaehoon on 22. 4. 3..
//

#ifndef RAISIM_SIMPLEPENDULUMPDCONTROLLER_H
#define RAISIM_SIMPLEPENDULUMPDCONTROLLER_H

#include "SingleLeggedRobotOperation.h"
#include "include/TrajectoryGenerator/CubicTrajectoryGenerator.h"

class SingleLeggedPDControllerOperation {
public:
    Eigen::VectorXd torque = Eigen::VectorXd(2);
    raisim::VecDyn position = raisim::VecDyn(3);
    raisim::VecDyn velocity = raisim::VecDyn(3);
    Eigen::VectorXd positionError = Eigen::VectorXd(2);
    Eigen::VectorXd velocityError = Eigen::VectorXd(2);
    Eigen::VectorXd desiredJointPosition = Eigen::VectorXd(2);
    Eigen::VectorXd desiredJointVelocity = Eigen::VectorXd(2);

    double desiredPosition = 0.0;
    double desiredVelocity = 0.0;

    double PGain;
    double DGain;

    SingleLeggedPDControllerOperation(SingleLeggedRobotOperation *robot) {
        mRobot = robot;
        setTrajectory();
        setPDGain(50.0, 2.5);
        torque[0] = 0.0;
    }

    void doControl();
    void zeroing();
    void updateTrajectory();
    void setTrajectory();
    void updateState();
    void computeControlInput();
    void setControlInput();
    void setPDGain(double PGain, double DGain);

private:
    SingleLeggedRobotOperation *mRobot;
    CubicTrajectoryGenerator mCubicTrajectoryGen1;
    CubicTrajectoryGenerator mCubicTrajectoryGen2;
    double mTorqueLimit = 10.0;
};


#endif //RAISIM_SIMPLEPENDULUMPDCONTROLLER_H
