//
// Created by jaehoon on 22. 6. 1.
//
#include <Eigen/Eigen>
#include <iostream>
#include "include/TrajectoryGenerator/CubicTrajectoryGenerator.h"
#include "include/TrajectoryGenerator/QuinticTrajectoryGenerator.h"

void CubicTrajectoryTest(double currentPosition, double goalPosition, double currentTime, double timeDuration)
{
    CubicTrajectoryGenerator trajGen;
    trajGen.updateTrajectory(currentPosition, goalPosition, currentTime, timeDuration);
    double realTime;
    double accumulatedPosition = 0.0;
    double accumulatedVelocity = 0.0;
    double dT = 0.001;
    for(int i = 0; i< timeDuration / dT +1; i++)
    {
        realTime = i * dT;
        std::cout<<"iteration : "<<i<<std::endl;
        std::cout<<"desired position : "<<trajGen.getPositionTrajectory(realTime)<<std::endl;
        std::cout<<"desired velocity : "<<trajGen.getVelocityTrajectory(realTime)<<std::endl;
        std::cout<<"desired acceleration : "<<trajGen.getAccelerationTrajectory(realTime)<<std::endl;
        accumulatedPosition += trajGen.getVelocityTrajectory(realTime) * dT;
        accumulatedVelocity += trajGen.getAccelerationTrajectory(realTime) * dT;
        std::cout<<"accumulated position : "<<accumulatedPosition<<std::endl;
        std::cout<<"accumulated velocity : "<<accumulatedVelocity<<std::endl;
    }
}

void QuinticTrajectoryTest(double currentPosition, double goalPosition, double currentTime, double timeDuration)
{
    QuinticTrajectoryGenerator trajGen;
    trajGen.updateTrajectory(currentPosition, goalPosition, currentTime, timeDuration);
    double realTime;
    double accumulatedPosition = 0.0;
    double accumulatedVelocity = 0.0;
    double dT = 0.001;
    for(int i = 0; i< timeDuration / dT +1; i++)
    {
        realTime = i * dT;
        std::cout<<"iteration : "<<i<<std::endl;
        std::cout<<"desired position : "<<trajGen.getPositionTrajectory(realTime)<<std::endl;
        std::cout<<"desired velocity : "<<trajGen.getVelocityTrajectory(realTime)<<std::endl;
        std::cout<<"desired acceleration : "<<trajGen.getAccelerationTrajectory(realTime)<<std::endl;
        accumulatedPosition += trajGen.getVelocityTrajectory(realTime) * dT;
        accumulatedVelocity += trajGen.getAccelerationTrajectory(realTime) * dT;
        std::cout<<"accumulated position : "<<accumulatedPosition<<std::endl;
        std::cout<<"accumulated velocity : "<<accumulatedVelocity<<std::endl;
    }
}
int main() {
//    CubicTrajectoryTest(0.0, 0.53, 0.0, 5.0);
//    QuinticTrajectoryTest(0.0, 0.53, 0.0, 5.0);
    double dT = 0.001;
    double timeDuration = 3.0;
    for(int i =0;i<int(timeDuration / dT); i++)
    {
        std::cout<<i<<std::endl;
    }

}