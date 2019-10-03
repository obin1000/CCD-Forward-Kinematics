//
// Created by obin1000 on 10-09-19.
//
#include <iostream>
#include <cmath>
#include "RobotArm.h"

RobotArm::RobotArm() {
    // Create size number of arm segment with default values
    arm.push_back(new ArmSegment(nullptr,10,0,-300,300));
    arm.push_back(new ArmSegment(arm[0],10,0,-300,300));
    arm.push_back(new ArmSegment(arm[1],10,0,-300,300));
}

void RobotArm::printArm() {
    for (auto & i : arm) {
        i->print();
    }
    std::cout << " \t\tHandLocation X: " << getGrijperX() << " Y: " << getGrijperY() << std::endl;
}

ArmSegment * RobotArm::getSegmentAt(int segment) {
    if(segment > arm.size()-1){
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

void RobotArm::grabAt(double grabX, double grabY, double marginOfError) {
    std::cout << "Ik ga je pakken ;) ... als je op " <<  grabX << " " << grabY << " bent" << std::endl;
    double error = 999999;
    int loops = 0;
    int currentSegment = (int) arm.size()-1;
    ArmSegment * tempSeg;
    std::vector<double> vectorHand;
    // Loop till the arm reaches an acceptable distance from the target
    while(error > marginOfError){
        if (loops++ == 10000) break;
        while(currentSegment >= 0) {
            arm[currentSegment]->rotateTo(grabX, grabY, getGrijperX(),getGrijperY());
            currentSegment--;
        }
        currentSegment = arm.size()-1;
        error = getError(getGrijperX(),getGrijperY(), grabX, grabY);
    }

    std::cout << "\nHAHAHA Hebbes!!" << std::endl;
    std::cout << "Handpositie\t X: " << getGrijperX() << " \tY: " << getGrijperY() << std::endl;
    std::cout << "Target\t\t X: " << grabX << " \t\t\tY: " << grabY << std::endl;
    std::cout << "In " << loops << " pogingen " << std::endl;
    std::cout << "Angles: ";
    for (auto & i : arm) {
        std::cout << "   " << i->getAngle();
    }
}

double RobotArm::getError(double handX, double handY, double targetX, double targetY) {
    std::vector<double> handToTarget = {handX - targetX, handY - targetY, 0};
    return ArmSegment::getVectorLen(handToTarget);
}
