//
// Created by jaehoon on 22. 6. 1.
//

#include "LoadCell.h"

void LoadCell::readData()
{
    mReadedData = 0;
    while(true)
    {
        mNumBytes = read(mSerialPort, &mReadBuf, sizeof(mReadBuf));
        if(mNumBytes == 1)
        {
            if(mReadBuf[0] == mLineFeedCode)
            {
                break;
            }
            else if(mReadBuf[0] == mSplitCode)
            {
                mIsDataStore = false;
            }
            else if(mReadBuf[0] == mNegativeValueCode)
            {
                mIsNegativeValue = true;
            }
            else if(mIsDataStore)
            {
                mReaded[mIdx] = (mReadBuf[0] - 48);
                mIdx++;
            }
        }
    }

    for(int i = 0; i<mIdx ; i++)
    {
        mReadedData += mReaded[i] * pow(10.0, mIdx - i - 1);
    }
    if(mIsNegativeValue)
    {
        mReadedData = -1.0 * mReadedData;
    }
    mSensoredWeight = mReadedData * mInclineWeight + mBiasWeight;
    mSensoredForce = mReadedData * mInclineForce + mBiasForce;

    // reset
    mIdx = 0;
    mIsDataStore = true;
    mIsNegativeValue = false;
}

void LoadCell::autoCalibration() {
    // it takes 2 seconds.
    std::cout<<"auto calibration is now running."<<std::endl;
    double tempSumedForce = 0;
    double tempSumedWeight = 0;
    double tempBiasForce = 0;
    double tempBiasWeight = 0;
    for(int i = 0; i<400 ; i++)
    {
        readData();
        tempSumedForce += getSensoredForce();
        tempSumedWeight += getSensoredWeight();
    }
    std::cout<<tempSumedWeight<<std::endl;
    tempBiasForce = tempSumedForce / 400.0;
    tempBiasWeight = tempSumedWeight / 400.0;

    std::cout<<mBiasWeight<<std::endl;
    mBiasForce -= tempBiasForce;
    mBiasWeight -= tempBiasWeight;
    std::cout<<mBiasWeight<<std::endl;
}

void LoadCell::flushData(int num) {
    for(int i = 0; i<num ; i++)
    {
        readData();
    }
}