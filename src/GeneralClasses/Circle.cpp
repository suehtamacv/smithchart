#include "include/GeneralClasses/Circle.h"

Circle::Circle(complex center, double radius) :
    Circle(center, radius, 0, 2 * PI)
{

}

Circle::Circle
(complex center, double radius, double initialPhase, double finalPhase) :
    center(center), rad(radius),
    initialPhase(initialPhase), finalPhase(finalPhase)
{
    if (radius <= 0)
        {
        radius = 1;
        }

    if (initialPhase > finalPhase)
        {
        std::swap(initialPhase, finalPhase);
        }

    createPoints();
}

void Circle::createPoints()
{
    double phaseStep = fabs(finalPhase - initialPhase) / numCirclePoints;
    for (double phase = initialPhase; phase <= finalPhase; phase += phaseStep)
        {
        CirclePoints.push_back(std::polar(rad, phase));
        }
}
