//
// Created by jaehoon on 22. 5. 25.
//

#ifndef RAISIM_SINGLELEGGEDROBOTOPERATION_H
#define RAISIM_SINGLELEGGEDROBOTOPERATION_H

#include "include/CAMEL/Robot.h"
#include "SingleLegCAN.h"

class SingleLeggedRobotOperation : public Robot {
public:
    SingleLeggedRobotOperation(raisim::World *world, std::string urdfPath, std::string name, SingleLegCAN *can) : Robot(
            world, urdfPath, name) {
        mCan = can;
        initialize();
    }

    void initialize() override;
    void visualize();
    void setTorque(Eigen::VectorXd torque);
    Eigen::VectorXd getQ();
    Eigen::VectorXd getQD();
    double getPlot1();
    double getPlot2();

private:
    SingleLegCAN *mCan;
    Eigen::VectorXd mJointPosition = Eigen::VectorXd(3);
    Eigen::VectorXd mJointVelocity = Eigen::VectorXd(3);

    double mHipOffset = 0.0; //
    double mKneeOffset = -3.302511324; //
    int mMotorKneeID = 0x141;
    int mMotorHipID = 0x143;
};


#endif //RAISIM_SINGLELEGGEDROBOTOPERATION_H
