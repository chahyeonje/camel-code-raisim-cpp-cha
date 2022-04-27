//
// Created by jaehoon on 22. 3. 31..
//

#ifndef RAISIM_SIMPLEPENDULUMSIMULATION_H
#define RAISIM_SIMPLEPENDULUMSIMULATION_H

#include "../../include/Simulation.h"
#include "../../include/SimulationThread.h"
#include "SimplePendulumRobot.h"
#include "SimplePendulumPDController.h"


//

class SimplePendulumSimulation : public Simulation {

public:
    SimplePendulumSimulation(raisim::World *world, double dT) : Simulation(world, dT) { ; }
    void task1(raisim::World *world, Controller *controller);

private:

};


#endif //RAISIM_SIMPLEPENDULUMSIMULATION_H
