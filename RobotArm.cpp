//
// Created by obin1000 on 10-09-19.
//
#include <iostream>
#include "RobotArm.h"

RobotArm::RobotArm(int size) {
    ArmSegment * temp = nullptr;
    // Create size number of arm segment with default values
    for (int i = 0; i < size; ++i) {
        arm.push_back(new ArmSegment(temp,10,10,0,360));
        temp = arm[i];
    }
}

void RobotArm::printArm() {
    for (auto & i : arm) {
        i->print();
    }
    std::cout << " \t\tHandLocation X: " << getGrijperX() << " Y: " << getGrijperY() << std::endl;
}

ArmSegment * RobotArm::getSegmentAt(int segment) {
    if(segment > arm.size()){
        return nullptr;
    }
    return arm[segment];
}

double RobotArm::getGrijperX() {
    return getSegmentAt((int) arm.size()-1)->getX();
}

double RobotArm::getGrijperY() {
    return getSegmentAt((int) arm.size()-1)->getY();
}

void RobotArm::grabAt(std::vector<double> grabLocation, double marginOfError) {
    std::cout << "Ik ga je pakken ;) ... als je op " << grabLocation[0] << " " << grabLocation[1] << " bent" << std::endl;
    double error = 999999;
    int loops = 0;
    int currentSegment = (int) arm.size()-1;
    ArmSegment * tempSeg;
    std::vector<double> vectorHand;
    printArm();
    // Loop till the arm reaches an acceptable distance from the target
    while(true){
        if (loops++ == 100) break;
        while(currentSegment >= 0) {
            tempSeg = arm[currentSegment];
            vectorHand = getVectorHand(tempSeg);
            tempSeg->rotateTo(grabLocation, vectorHand);
            std::cout << currentSegment << " SEG " << tempSeg << std::endl;
            currentSegment--;
            //printArm();
        }
        currentSegment = arm.size()-1;
        // error = getError(getGrijperX(),getGrijperY(),grabLocation[0],grabLocation[1]);

    }

    std::cout << "HAHAHA Hebbes!! " << getGrijperX() << " " << getGrijperY();

}
// Get the vector to the end of the arm from given segment
std::vector<double> RobotArm::getVectorHand(ArmSegment * fromSegment) {
    std::vector<double > veccie(3);
    double armX = arm[arm.size()-1]->getX();
    double armY = arm[arm.size()-1]->getY();
    double segmentX = fromSegment->getX();
    double segmentY = fromSegment->getY();
    veccie[0] = armX  - segmentX;
    veccie[1] = armY - segmentY;
    veccie[2] = 0;
    return veccie;
}

double RobotArm::getError(double handX, double handY, double targetX, double targetY) {
    return (double) (handX - targetX) + (handY - targetY);
}
