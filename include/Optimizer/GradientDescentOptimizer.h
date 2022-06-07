//
// Created by jaehoon on 22. 6. 1.
//

#ifndef RAISIM_GRADIENTDESCENTOPTIMIZER_H
#define RAISIM_GRADIENTDESCENTOPTIMIZER_H

#include <Eigen/Eigen>
#include <cmath>

class GradientDescentOptimizer {
public:
    void computeGradient();
    void updateStates();
    void checkTerminateCondition();
    void solve();
    void setStepSize(double stepSize) { mStepSize = stepSize; }
    void setMaximumIteration(int maximumIteration) { mMaximumIteration = maximumIteration; }
    void setTerminateCondition(double terminateCondition) { mTerminateCondition = terminateCondition; }
    void setObjectiveFunction(double (*objectiveFunction)(Eigen::VectorXd)){ mObjectiveFunction = objectiveFunction; }
    void setInitialState(Eigen::VectorXd initialState);
    double getFunctionValue(Eigen::VectorXd x){return mObjectiveFunction(x);}
    Eigen::VectorXd getState(){return mState; }

private:
    bool mTerminateFlag = false;
    int mIteration = 0;
    int mMaximumIteration = 1000;
    int mDimension;
    double mDelta = 1e-6;
    double mStepSize = 0.01;
    double mTerminateCondition = 1e-6;
    double mRMSGradient;
    double (*mObjectiveFunction)(Eigen::VectorXd);
    Eigen::VectorXd mState;
    Eigen::VectorXd mTempState;
    Eigen::VectorXd mGradient;
};


#endif //RAISIM_GRADIENTDESCENTOPTIMIZER_H
