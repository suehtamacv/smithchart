#ifndef IMPEDANCE_H
#define IMPEDANCE_H

#include <complex>

class Admittance;

class Impedance
{
public:
    Impedance(std::complex<double> impedance);
    Impedance(double Abs, double Theta);

    Admittance toAdmittance();

private:
    std::complex<double> impedance;
};

#endif // IMPEDANCE_H
