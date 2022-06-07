//
// Created by jaehoon on 22. 6. 1.
//

#include "GradientDescentOptimizer.h"
#include <iostream>
void GradientDescentOptimizer::setInitialState(Eigen::VectorXd initialState) {
    mState = initialState;
    mDimension = mState.size();
    mTempState = Eigen::VectorXd(mDimension);
    mGradient = Eigen::VectorXd(mDimension);
    mGradient.setZero();
}

void GradientDescentOptimizer::computeGradient() {
    double functionValue = getFunctionValue(mState);
    for(int i = 0 ; i < mDimension ; i++)
    {
        mTempState = mState;
        mTempState[i] += mDelta;
        mGradient[i] = (getFunctionValue(mTempState) - functionValue) / mDelta;
    }
    mRMSGradient = pow(mGradient.dot(mGradient) / mDimension , 0.5);
}

void GradientDescentOptimizer::updateStates() {
    mState = mState - mStepSize * mGradient;
}

void GradientDescentOptimizer::checkTerminateCondition() {
    if(mIteration == mMaximumIteration)
    {
        mTerminateFlag = true;
        std::cout<<"Gradient Descent Optimizer is completed. (Maximum iteration)"<<std::endl;
    }
    else if(mRMSGradient < mTerminateCondition)
    {
        mTerminateFlag = true;
        std::cout<<"Gradient Descent Optimizer is completed. (Terminate condition)"<<std::endl;
    }
}

void GradientDescentOptimizer::solve() {
    for(int i = 0 ; i < mMaximumIteration ; i++)
    {
        mIteration++;
        computeGradient();
        updateStates();
        checkTerminateCondition();
        if(mTerminateFlag)
        {
            break;
        }
    }
}