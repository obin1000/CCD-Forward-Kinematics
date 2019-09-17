#include <iostream>
#include "RobotArm.h"


int main() {
    RobotArm arm;
    std::vector<double> v1 = {15.4,10.2,0.0};
    std::vector<double> v2 = {1.1,2.2,0.0};
    arm.grabAt(v1, 1);
    std::cout << arm.getSegmentAt(0)->getTotalAngle();
    return 0;
}
