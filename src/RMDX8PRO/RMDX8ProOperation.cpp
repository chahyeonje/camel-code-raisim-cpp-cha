//
// Created by jaehoon on 22. 4. 13..
//

#include "RMDX8ProOperation.h"

double deg2rad = 3.141592 / 180.0;
double rad2deg = 180.0 / 3.141592;

int main(){
    std::string canName_temp = "can8";
    std::string bitRate = "1000000";
    char *canName = "can8";
    CanMotorX8Pro canX8pro(canName, canName_temp, bitRate);
    if (canX8pro.getSock() < 0) { return -1; }

    std::string urdfPath = "\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_RMDX8_pro.urdf";
    std::string name = "RMDX8Pro";
    raisim::World world;
    RMDX8ProOperation realRobot = RMDX8ProOperation(&world, 30);
    RMDX8ProRobot rmdX8 = RMDX8ProRobot(&world, urdfPath, name, &canX8pro);
    RMDX8ProPDContorller PDcontroller = RMDX8ProPDContorller(&rmdX8);

    raisim::RaisimServer server(&world);
    server.launchServer(8080);
    sleep(5);
    int iteration = 0;
    PDcontroller.setTrajectory(180.0 * deg2rad, 0.0);
    while(true)
    {
        iteration++;
        PDcontroller.doControl();
        if((PDcontroller.isTerminateCondition())||(iteration > 1000))
        {
            break;
        }
        usleep(1000);
        std::cout<<"current position : "<<PDcontroller.position<<std::endl;
    }
    sleep(10);
    canX8pro.turnOffMotor(0x141);
    server.killServer();
}

