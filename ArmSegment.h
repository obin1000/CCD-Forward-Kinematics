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
    void rotate(double angle_);
    double getTotalAngle();
    ArmSegment * getVoorganger();
    void checkAngle();
    void print();
    void rotateTo(const std::vector<double>& targetEndpoint, const std::vector<double>& armEndpoint);
    std::vector<double> crossproduct(std::vector<double> v1,std::vector<double> v2);
    double getVectorLen(std::vector<double> vec);
    double getDotProduct(std::vector<double> vec1, std::vector<double> vec2);
};


#endif //WEEK_1_ARMSEGMENT_H
