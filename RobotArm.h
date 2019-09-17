//
// Created by obin1000 on 10-09-19.
//

#ifndef WEEK_1_ROBOTARM_H
#define WEEK_1_ROBOTARM_H


#include <vector>
#include "ArmSegment.h"

class RobotArm {
private:
    // Use vector as array
    std::vector<ArmSegment *> arm;

public:
    RobotArm(int size);
    void printArm();
    ArmSegment * getSegmentAt(int segment);
    double getGrijperX();
    double getGrijperY();
    void grabAt(std::vector<double> grabLocation, double marginOfError);
    std::vector<double> getVectorHand(ArmSegment *fromSegment);
    double getError(double handX, double handY, double targetX, double targetY);

};


#endif //WEEK_1_ROBOTARM_H
