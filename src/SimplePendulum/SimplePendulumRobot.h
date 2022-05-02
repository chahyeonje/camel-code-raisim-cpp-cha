//
// Created by jaehoon on 22. 4. 3..
//

#ifndef RAISIM_SIMPLEPENDULUMROBOT_H
#define RAISIM_SIMPLEPENDULUMROBOT_H

#include "include/CAMEL/Robot.h"

class SimplePendulumRobot: public Robot{
public:
    SimplePendulumRobot(raisim::World *world, std::string urdfPath, std::string name) : Robot(world, urdfPath, name){
        initialize();}
    void initialize() override;
    double getQ();
    double getQD();
};

void SimplePendulumRobot::initialize() {
    Eigen::VectorXd initialJointPosition(robot->getGeneralizedCoordinateDim());
    initialJointPosition.setZero();
    initialJointPosition[0] = 1.57;
    robot->setGeneralizedCoordinate(initialJointPosition);
}

double SimplePendulumRobot::getQ(){
    return this->robot->getGeneralizedCoordinate()[0];
}

double SimplePendulumRobot::getQD(){
    return this->robot->getGeneralizedVelocity()[0];
}

#endif //RAISIM_SIMPLEPENDULUMROBOT_H
