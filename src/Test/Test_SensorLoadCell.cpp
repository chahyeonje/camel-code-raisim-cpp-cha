//
// Created by jaehoon on 22. 6. 9.
//
#include "include/Sensor/LoadCell.h"

int main()
{
    LoadCell sensorLoadcell;
    bool isTermination = true;
    int iteration = 0;
    int rawData = 0;
    double force = 0.0;
    double weight = 0.0;
    while(isTermination)
    {
        iteration++;
        if(iteration == 16000){isTermination = false;}
        sensorLoadcell.readData();
        force = sensorLoadcell.getSensoredForce();
        weight = sensorLoadcell.getSensoredWeight();
        rawData = sensorLoadcell.getRawData();
//        std::cout<<"Sensored force[N] : "<<force<<std::endl;
        std::cout<<"Sensored weight[g] : "<<weight<<std::endl;
        std::cout<<"Raw data : "<<rawData<<std::endl;
    }
}