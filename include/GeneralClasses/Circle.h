#ifndef CIRCLESEGMENT_H
#define CIRCLESEGMENT_H

#include <complex>
#include <vector>
#define PI 3.141592653589793238462643383279502884L

typedef std::complex<double> complex;

class Circle
{
public:
    Circle(complex center, double radius);
    Circle(complex center, double radius, double initialPhase, double finalPhase);

private:
    complex center;
    double radius;
    double initialPhase;
    double finalPhase;

    static constexpr unsigned int numCirclePoints = 200;
    std::vector<complex> CirclePoints;
    void createPoints();
};

#endif // CIRCLESEGMENT_H
