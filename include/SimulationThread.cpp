//
// Created by jaehoon on 22. 4. 26.
//

#include "SimulationThread.h"

void SimulationThread::Run() {
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        mController -> doControl();
        mWorld->integrate();
    }
}