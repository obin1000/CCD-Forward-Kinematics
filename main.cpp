#include <iostream>
#include "RobotArm.h"
#include <math.h>


int main() {
    RobotArm arm(3);
    std::vector<double> v1 = {15.4,10.2,0.0};
    std::vector<double> v2 = {1.1,2.2,0,0};
    arm.grabAt(v1, 1);

    return 0;
}
