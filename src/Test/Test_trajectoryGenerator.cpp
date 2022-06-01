//
// Created by jaehoon on 22. 6. 1.
//
#include <Eigen/Eigen>
#include <iostream>
#include "include/TrajectoryGenerator/CubicTrajectoryGenerator.h"

int main() {
    CubicTrajectoryGenerator trajGen;
    trajGen.updateTrajectory(2.5, 5.3, 0.0, 1.0);
    double currentTime = 0.0;
    for(int i = 0; i< 101; i++)
    {
        currentTime = i * 0.01;
        std::cout<<trajGen.getPositionTrajectory(currentTime)<<std::endl;
        std::cout<<trajGen.getVelocityTrajectory(currentTime)<<std::endl;
        std::cout<<trajGen.getAccelerationTrajectory(currentTime)<<std::endl;
    }
}