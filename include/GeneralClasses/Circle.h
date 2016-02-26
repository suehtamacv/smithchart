#ifndef CIRCLE_H
#define CIRCLE_H

#include "Complex.h"
#include <vector>

#define PI 3.141592653589793238462643383279502884

class Circle
{
public:
    Circle(complex center, double rad);
    Circle(complex center, double rad, double initialPhase, double finalPhase);

    Circle operator *(double k)
    {
        return Circle(k * center, k * rad, initialPhase, finalPhase);
    }

    inline double x()
    {
        return center.real();
    }

    inline double y()
    {
        return center.imag();
    }

    inline double radius()
    {
        return rad;
    }

private:
    complex center;
    double rad;
    double initialPhase;
    double finalPhase;

    static constexpr unsigned int numCirclePoints = 500;
    std::vector<complex> CirclePoints;
    void createPoints();
};

#endif // CIRCLE_H
