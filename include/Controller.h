//
// Created by jaehoon on 22. 3. 31..
//

#ifndef RAISIM_CONTROLLER_H
#define RAISIM_CONTROLLER_H

#include "Robot.h"

class Controller {
public:
    Controller(Robot *robot) {
        mRobot = robot;
    }
    Robot *getRobot(){return mRobot;}
    virtual void doControl() = 0;

    virtual void setTrajectory() = 0;

    virtual void updateState() = 0;

    virtual void computeControlInput() = 0;

    virtual void setControlInput() = 0;

private:
    Robot *mRobot;

};


#endif //RAISIM_CONTROLLER_H
