//
// Created by jaehoon on 22. 3. 31..
//

#ifndef RAISIM_SIMPLEPENDULUMSIMULATION_H
#define RAISIM_SIMPLEPENDULUMSIMULATION_H

#include "include/CAMEL/Simulation.h"
#include "SingleLeggedRobot.h"
#include "SingleLeggedPDController.h"
#include "SingleLeggedIDController.h"

class SingleLeggedSimulation : public Simulation {

public:
    SingleLeggedSimulation(raisim::World *world, double dT) : Simulation(world, dT) { ; }

    void writeToCSVfile(std::string name, Eigen::MatrixXd matrix)
    {
        std::ofstream file(name.c_str());
        for(int  i = 0; i < matrix.rows(); i++)
        {
            for(int j = 0; j < matrix.cols(); j++)
            {
                std::string str = std::to_string(matrix(i,j));
                if(j+1 == matrix.cols()){
                    file<<str;
                }else{
                    file<<str<<',';
                }
            }
            file<<'\n';
        }
    }

private:

};


#endif //RAISIM_SIMPLEPENDULUMSIMULATION_H
