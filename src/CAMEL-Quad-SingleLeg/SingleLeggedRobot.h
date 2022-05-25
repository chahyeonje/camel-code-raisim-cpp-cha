//
// Created by jaehoon on 22. 4. 3..
//

#ifndef RAISIM_SIMPLEPENDULUMROBOT_H
#define RAISIM_SIMPLEPENDULUMROBOT_H

#include "include/CAMEL/Robot.h"

class SingleLegRobot: public Robot{
public:
    SingleLegRobot(raisim::World *world, std::string urdfPath, std::string name) : Robot(world, urdfPath, name){
        initialize();}
    void initialize() override;
    raisim::VecDyn getQ();
    raisim::VecDyn getQD();
    double getPlot1();
    double getPlot2();
};



#endif //RAISIM_SIMPLEPENDULUMROBOT_H
