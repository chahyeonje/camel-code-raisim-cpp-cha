//
// Created by jaehoon on 22. 6. 1.
//

#ifndef RAISIM_CUBICTRAJECTORYGENERATOR_H
#define RAISIM_CUBICTRAJECTORYGENERATOR_H
#include <Eigen/Eigen>
#include <cmath>

class CubicTrajectoryGenerator {
public:
    CubicTrajectoryGenerator()
    {
        mMatrixA << 2.0, -2.0, 1.0, 1.0, -3.0, 3.0, -2.0, -1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0;
    }
    void updateTrajectory(double currentPosition,double goalPosition,double currentTime,double timeDuration);
    void calculateCoefficient();
    double getPositionTrajectory(double currentTime);
    double getVelocityTrajectory(double currentTime);
    double getAccelerationTrajectory(double currentTime);

private:
    Eigen::MatrixXd mMatrixA = Eigen::MatrixXd(4, 4);
    Eigen::MatrixXd mCoefficient = Eigen::MatrixXd(4, 1);
    Eigen::MatrixXd mFunctionValue = Eigen::MatrixXd(4, 1);
    double mReferenceTime;
    double mTimeDuration;
};


#endif //RAISIM_CUBICTRAJECTORYGENERATOR_H
