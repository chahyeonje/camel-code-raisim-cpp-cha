//
// Created by jaehoon on 22. 4. 3..
//

#ifndef RAISIM_SIMULATIONTHREAD_H
#define RAISIM_SIMULATIONTHREAD_H

#include "raisim/RaisimServer.hpp"
#include "raisim/World.hpp"
#include "Simulation.h"
#include "Controller.h"

class SimulationThread {
public:
    SimulationThread(raisim::World *world, Controller *controller){
        mWorld = world;
        mController = controller;
    }

    void Run();

private:
    raisim::World *mWorld;
    Controller *mController;

};

void SimulationThread::Run() {
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        mController -> doControl();
        mWorld->integrate();
    }
}
#endif //RAISIM_SIMULATIONTHREAD_H
