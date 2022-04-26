//
// Created by jaehoon on 22. 4. 13..
//

#ifndef RAISIM_OPERATION_H
#define RAISIM_OPERATION_H

#include "../../raisim/linux/include/raisim/math.hpp"
#include "../../raisim/linux/include/raisim/RaisimServer.hpp"
#include "../../raisim/linux/include/raisim/World.hpp"

class Operation {

public:
    Operation(raisim::World *world, double fps) {
        this->mWorld = world;
        mWorld->setTimeStep(1/fps);
        mWorld->addGround();
        raisim::Vec<3> gravity = {0.0, 0.0, 0.0};
        mWorld->setGravity(gravity);
    }

private:
    raisim::World *mWorld;
};

#endif //RAISIM_OPERATION_H
