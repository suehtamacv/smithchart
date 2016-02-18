#ifndef ADMITTANCE_H
#define ADMITTANCE_H

#include <complex>

class Impedance;

class Admittance
{
public:
    Admittance(std::complex<double> admittance);
    Admittance(double Abs, double Theta);

    Impedance toImpedance();

private:
    std::complex<double> admittance;
};

#endif // ADMITTANCE_H
