//
// Created by jaehoon on 22. 5. 25.
//

#include "SingleLeggedOperation.h"
#include "mainwindow.h"
#include <QApplication>
#include <thread>

double deg2rad = 3.141592 / 180.0;
double rad2deg = 180.0 / 3.141592;

void thread1task(bool *button1Pressed, bool *button2Pressed, bool *button3Pressed, bool *button4Pressed,
                 bool *button5Pressed, bool *button6Pressed) {
    std::string canName_temp = "can0";
    std::string bitRate = "1000000";
    char *canName = "can0";
    SingleLegCAN can(canName, canName_temp, bitRate);

    std::string urdfPath = "\\home\\jaehoon\\raisimLib\\camel-code-raisim-cpp\\rsc\\camel_single_leg\\camel_single_leg.urdf";
    std::string name = "singleLeg";
    raisim::World world;
    SingleLeggedOperation realRobot = SingleLeggedOperation(&world, 30);
    SingleLeggedRobotOperation singleLeg = SingleLeggedRobotOperation(&world, urdfPath, name, &can);
//    SingleLeggedPDController PDcontroller = SingleLeggedPDController(&singleLeg);
    raisim::RaisimServer server(&world);

    int motorKnee = 0x141;
    int motorHip = 0x142;
    while (true) {
        usleep(1000);
        can.setTorque(motorHip, 0.0);
        can.setTorque(motorKnee, 0.0);
        singleLeg.visualize();

        if (*button1Pressed) {
            // CAN initialize
            if (can.getSock() < 0) {
                std::cout << "Failed to creat CAN" << std::endl;
                break;
            }
            std::cout << "Success to initialize CAN communication" << std::endl;
            *button1Pressed = false;
        }

        if (*button2Pressed) {
            // Raisim initialize

            server.launchServer(8080);
            sleep(5);
            *button2Pressed = false;
            std::cout << "Success to initialize Raisim" << std::endl;
        }

        if (*button3Pressed) {
            // Motor On
            can.turnOnMotor(motorKnee);
            can.turnOnMotor(motorHip);
            *button3Pressed = false;
        }

        if (*button4Pressed) {
            // Motor Off
            can.turnOffMotor(motorKnee);
            can.turnOffMotor(motorHip);
            *button4Pressed = false;
        }

        if (*button5Pressed) {
            // Start Control
//            int iteration = 0;
//            while (true) {
//                iteration++;
//                PDcontroller.doControl();
//                if ((PDcontroller.isTerminateCondition()) || (iteration > 1000)) {
//                    rmdX8.motorOff(0x141);
//                    break;
//                }
//                usleep(1000);
//                std::cout << "current position : " << PDcontroller.position << std::endl;
//            }
            *button5Pressed = false;
        }

        if (*button6Pressed) {
//            // Generate new trajectory
//            PDcontroller.setTrajectory(3.141592 * 1.0, 0.0);
            *button6Pressed = false;
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    std::thread thread1(thread1task, &w.button1, &w.button2, &w.button3, &w.button4, &w.button5, &w.button6);
    w.show();

    return a.exec();
}


