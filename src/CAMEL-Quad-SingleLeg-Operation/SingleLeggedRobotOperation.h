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

    raisim::VecDyn getQ();

    raisim::VecDyn getQD();

    double getPlot1();

    double getPlot2();

private:
    SingleLegCAN *mCan;
    Eigen::VectorXd mJointPosition = Eigen::VectorXd(3);
    double mHipOffset = 0.0; // => -90 deg
    double mKneeOffset = 2.62547; //

};


#endif //RAISIM_SINGLELEGGEDROBOTOPERATION_H
