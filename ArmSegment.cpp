//
// Created by obin1000 on 10-09-19.
//
#include <math.h>
#include <iostream>
#include "ArmSegment.h"

ArmSegment::ArmSegment(ArmSegment *voorganger_, double length_, double angle_, double maxHoekOnder_,
                       double maxHoekBoven_) {
    length = length_;
    voorganger = voorganger_;
    // Calculate radians from degrees
    maxHoekOnder = (maxHoekOnder_ * M_PI / 180.0);
    maxHoekBoven = (maxHoekBoven_ * M_PI / 180.0);
    angle = (angle_ * M_PI / 180.0);
    checkAngle();
}

// Get current angle of this segment
double ArmSegment::getAngle() {
    return angle;
}

// Recursive add all angles of all arm segments
double ArmSegment::getTotalAngle() {
    if (!voorganger) {
        return angle;
    }
    return angle + voorganger->getTotalAngle();
}


double ArmSegment::getX() {
    if (!voorganger) {
        return length * sin(getTotalAngle());
    }
    return voorganger->getX() + length * sin(getTotalAngle());
}

double ArmSegment::getY() {
    if (!voorganger) {
        return length * cos(getTotalAngle());
    }
    return voorganger->getY() + length * cos(getTotalAngle());
}
// Rotate this segment to a target
void ArmSegment::rotateTo(double targetX, double targetY, double handX, double handY) {
    // Create vectors to the target and the hand and calculate the angle between them
    std::vector<double> mount = getMountPoint();
    std::vector<double> target = getVector(targetX, targetY, mount[0], mount[1]);
    std::vector<double> hand = getVector(handX, handY, mount[0], mount[1]);
    double turnAngle = getVectorAngle(target,hand);

    // Get cross product to determine rotation direction
    if (crossproduct(target, hand)[2] > 0.0) {
        angle -= turnAngle;
    }
    else {
        angle += turnAngle;
    }
    checkAngle();
}

void ArmSegment::print() {
    std::cout << " X: " << getX();
    std::cout << " \t\tY: " << getY();
    std::cout << " \t\tTotalAngle: " << getTotalAngle() << std::endl;
}

void ArmSegment::checkAngle(){
    // Check voor demping overscheiding
//    if (angle < maxHoekOnder) {
//        std::cout << " Potverdikkie, die draaihoek is veel te klein " << angle << " min is " << maxHoekOnder
//                  << std::endl;
//        angle = maxHoekOnder;
//    }
//    if (angle > maxHoekBoven) {
//        std::cout << " Potverdikkie, die draaihoek is veel te groot " << angle << " max is " << maxHoekBoven
//                  << std::endl;
//        angle = maxHoekBoven;
//    }
}

std::vector<double> ArmSegment::getMountPoint() {
    if(!voorganger){
        return {0,0,0};
    }
    return {voorganger->getX(),voorganger->getY(),0};
}


// Bestaat hier echt geen standaard lib voor?!
std::vector<double> ArmSegment::crossproduct(std::vector<double> v1,std::vector<double> v2)
{
    std::vector<double> cross(3);
    cross[0] = v1[1] * v2[2] - v1[2] * v2[1];
    cross[1] = v1[2] * v2[0] - v1[0] * v2[2];
    cross[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return cross;
}

double ArmSegment::getVectorLen(std::vector<double> vector) {
    double sum = (vector[0] * vector[0]) + (vector[1] * vector[1]);
    if (sum < 0) { return 0;}
    return sqrt(sum);
}

double ArmSegment::getDotProduct(std::vector<double> vec1, std::vector<double> vec2) {
    return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
}

std::vector<double> ArmSegment::getVector(double X1, double Y1, double X2, double Y2) {
    std::vector<double> temp(3);
    temp[0] = X1 - X2;
    temp[1] = Y1 - Y2;
    temp[2] = 0;
    return temp;
}
// A vector looks like: [X,Y,Z]
// a * b = |a| |b| cos(hoek)
// acos((a * b) / ( len(a) * len(b))) = hoek
double ArmSegment::getVectorAngle(std::vector<double> v1, std::vector<double> v2) {
    double dotProduct = getDotProduct(v1, v2);
    double keertje = (getVectorLen(v1) * getVectorLen(v2));
    double hoekkie;
    if (keertje == 0){
        hoekkie = 0;
    }else{
        hoekkie = dotProduct / keertje;
    }
    if(hoekkie < -1.0) hoekkie = -1.0;
    if(hoekkie > 1.0) hoekkie = 1.0;
    return acos(hoekkie);
}
