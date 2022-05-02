//
// Created by jaehoon on 22. 4. 13..
//

#ifndef RAISIM_RMDX8PROOPERATION_H
#define RAISIM_RMDX8PROOPERATION_H

#include "include/CAMEL/Operation.h"
#include "RMDX8ProRobot.h"
#include "RMDX8ProPDController.h"

class RMDX8ProOperation : public Operation{
public:
    RMDX8ProOperation(raisim::World *world, double fps) : Operation(world, fps){;}

private:
};


#endif //RAISIM_RMDX8PROOPERATION_H
