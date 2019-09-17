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
    std::vector<double> vectorHand; // Vector from this segment to the hand


public:
    ArmSegment(ArmSegment * armSegment, double length, double angle, double maxHoekOnder, double maxHoekBoven);
    double getX();
    double getY();
    double getAngle();
    double getTotalAngle();
    std::vector<double> getMountPoint();
    void checkAngle();
    void print();
    void rotateTo(const std::vector<double>& targetEndpoint, double handX, double handY);
    std::vector<double> crossproduct(std::vector<double> v1,std::vector<double> v2);
    double getVectorLen(std::vector<double> vec);
    double getDotProduct(std::vector<double> vec1, std::vector<double> vec2);
    std::vector<double> getVectorHand(double armX, double armY);
};


#endif //WEEK_1_ARMSEGMENT_H
