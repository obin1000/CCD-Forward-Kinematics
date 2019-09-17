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
    maxHoekOnder = maxHoekOnder_ * M_PI / 180.0;
    maxHoekBoven = maxHoekBoven_ * M_PI / 180.0;
    angle = angle_ * M_PI / 180.0;
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
    return (angle + voorganger->getTotalAngle());
}


double ArmSegment::getX() {
    if (!voorganger) {
        return length * sin(getTotalAngle());
    }
    double result = (voorganger->getX() + length * sin(getTotalAngle()));
    return result;
}

double ArmSegment::getY() {
    if (!voorganger) {
        return length * cos(getTotalAngle());
    }
    double result = (voorganger->getY() + length * cos(getTotalAngle()));
    return result;
}

// Rotate this segment
void ArmSegment::rotate(double angle_) {
    // Berkenen de nieuwe hoek met de rotatie
    angle += (angle_ * M_PI / 180.0);
    checkAngle();
}

// Rotate this segment to a target
// A vector looks like: [X,Y,Z]
// a * b = |a| |b| cos(hoek)
// (a * b) / ( len(a) * len(b)) = cos(hoek)
void ArmSegment::rotateTo(const std::vector<double>& targetVec, const std::vector<double>& armVec) {
    // Get dot product and calculate rotation angle
    double dotProduct = getDotProduct(targetVec,armVec);
    double turnAngle = (dotProduct/ (getVectorLen(targetVec)*getVectorLen(armVec)));

    if(turnAngle < -1.0) turnAngle = -1.0;
    if(turnAngle > 1.0) turnAngle = 1.0;

    print();
    // Get cross product for rotation direction
    std::vector<double> crossProduct = crossproduct(targetVec,armVec);

    if (crossProduct[2] > 0.0) {
        angle -= turnAngle;
    }
    else {
        angle += turnAngle;
    }
    checkAngle();
}

ArmSegment *ArmSegment::getVoorganger() {
    return voorganger;
}

void ArmSegment::print() {
    std::cout << " X: " << getX();
    std::cout << " \t\tY: " << getY();
    std::cout << " \t\tAngle: " << getAngle();
    std::cout << " \t\tTotalAngle: " << getTotalAngle() << std::endl;
}

void ArmSegment::checkAngle(){
    // Check voor demping overscheiding
    if (angle < maxHoekOnder) {
        std::cout << " Potverdikkie, die draaihoek is veel te klein " << angle << " min is " << maxHoekOnder
                  << std::endl;
        angle = maxHoekOnder;
    }
    if (angle > maxHoekBoven) {
        std::cout << " Potverdikkie, die draaihoek is veel te groot " << angle << " max is " << maxHoekBoven
                  << std::endl;
        angle = maxHoekBoven;
    }
}

// Bestaat hier echt geen standaard lib voor?!
std::vector<double> ArmSegment::crossproduct(std::vector<double> v1,std::vector<double> v2)
{
    std::vector<double> cross(v1.size());
    cross[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
    cross[1] = -(v1[2]*v2[0]) - (v1[0]*v2[2]);
    cross[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
    return cross;
}

double ArmSegment::getVectorLen(std::vector<double> vector) {
    double sum = (vector[0] * vector[0]) + (vector[1] * vector[1]);
    if (sum < 0) {sum = 0;}
    return sqrt(sum);
}

double ArmSegment::getDotProduct(std::vector<double> vec1, std::vector<double> vec2) {
    double result = (vec1[0] * vec2[0]) + (vec1[1] * vec2[1]) + (vec1[2] * vec2[2]);
    return result;
}
