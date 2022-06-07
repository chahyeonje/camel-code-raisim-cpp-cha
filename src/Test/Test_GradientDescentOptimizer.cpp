//
// Created by jaehoon on 22. 6. 1.
//
#include "include/Optimizer/GradientDescentOptimizer.h"
#include <iostream>



double objFunc_main(Eigen::VectorXd x)
{
    return (x[0] - 5.0)*(x[0] - 5.0) + (x[1] - 3.0)*(x[1] - 3.0);
}

int main(){
    GradientDescentOptimizer GDOptimizer;
    double (*objFunc)(Eigen::VectorXd) = objFunc_main;
    GDOptimizer.setObjectiveFunction(objFunc);

    Eigen::VectorXd y = Eigen::VectorXd(2);
    y << 0.0, 0.0;
    GDOptimizer.setInitialState(y);
    GDOptimizer.solve();
    std::cout<<GDOptimizer.getState()<<std::endl;
}