//
// Created by jaehoon on 22. 6. 1.
//

#ifndef RAISIM_GRADIENTDESCENTOPTIMIZER_H
#define RAISIM_GRADIENTDESCENTOPTIMIZER_H

#include <Eigen/Eigen>
#include <cmath>

// TODO: make other methods, run test code, and measure time duration
class GradientDescentOptimizer {
public:
    void setStepSize(double stepSize) { mStepSize = stepSize; }
    void setMaximumIteration(int maximumIteration) { mMaximumIteration = maximumIteration; }
    void setTerminateCondition(double terminateCondition) { mTerminateCondition = terminateCondition; }
    void setObjectiveFunction(double (*objectiveFunction)(Eigen::VectorXd)){ mObjectiveFunction = objectiveFunction;}
    double getFunctionValue(Eigen::VectorXd x){return mObjectiveFunction(x);}

private:
    bool mterminateFlag = false;
    int mIteration = 0;
    int mMaximumIteration = 1000;
    double mDelta = 1e-6;
    double mStepSize = 0.01;
    double mTerminateCondition = 1e-6;
    double (*mObjectiveFunction)(Eigen::VectorXd);
};


#endif //RAISIM_GRADIENTDESCENTOPTIMIZER_H
