//
// Created by jaehoon on 22. 3. 31..
//

#ifndef RAISIM_CAMELTHREAD_H
#define RAISIM_CAMELTHREAD_H

#include "raisim/RaisimServer.hpp"
#include "raisim/World.hpp"
#include "Simulation.h"

class CAMELThread {
public:
    CAMELThread(Simulation *simulation){
        this->mSimulation = simulation;
    }

    void Run();

private:
    Simulation *mSimulation;

};

void CAMELThread::Run() {
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
//        mSimulation->getWorld()->integrate();
    }
}

#endif //RAISIM_CAMELTHREAD_H
