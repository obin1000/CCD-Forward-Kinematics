//
// Created by obin1000 on 10-09-19.
//

#ifndef WEEK_1_ARMSEGMENT_H
#define WEEK_1_ARMSEGMENT_H
#include <vector>

class ArmSegment {
private:
    double angle;               // Hoek van dik segment ten opzicht van het segment ervoor.
    double length;              // Lengte van dit segment.
    double maxHoekOnder;        // Demping rotatie naar onder.
    double maxHoekBoven;        // Demping rotatie naar boven.
    ArmSegment * voorganger{};  // Segment voorafgaand aan dit segment, nullptr als het begin segment is.


public:
    ArmSegment(ArmSegment * armSegment, double length, double angle, double maxHoekOnder, double maxHoekBoven);
    double getX();
    double getY();
    double getAngle();
    double getTotalAngle();
    std::vector<double> getMountPoint();
    void checkAngle();
    void print();
    void rotateTo(double targetX, double targetY, double handX, double handY);
    static std::vector<double> crossproduct(std::vector<double> v1,std::vector<double> v2);
    static double getVectorLen(std::vector<double> vec);
    static double getDotProduct(std::vector<double> vec1, std::vector<double> vec2);
    static std::vector<double> getVector(double X1, double Y1, double X2, double Y2);
    static double getVectorAngle(std::vector<double> v1, std::vector<double> v2);
};


#endif //WEEK_1_ARMSEGMENT_H
