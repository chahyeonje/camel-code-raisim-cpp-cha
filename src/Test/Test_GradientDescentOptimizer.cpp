//
// Created by jaehoon on 22. 6. 1.
//
#include "include/Optimizer/GradientDescentOptimizer.h"
#include <iostream>



double objFunc_main(Eigen::VectorXd x)
{
    return (x[0] - 5.0)*(x[0] - 5.0);
}

int main(){
    GradientDescentOptimizer GDOptimizer;
    double (*objFunc)(Eigen::VectorXd) = objFunc_main;
    GDOptimizer.setObjectiveFunction(objFunc);

    Eigen::VectorXd y = Eigen::VectorXd(1);
    y[0] = 5.0;
    std::cout<<GDOptimizer.getFunctionValue(y)<<std::endl;
}