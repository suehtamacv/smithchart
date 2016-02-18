#include "include/GeneralClasses/Admittance.h"
#include "include/GeneralClasses/Impedance.h"

Admittance::Admittance(std::complex<double> admittance) :
    admittance(admittance)
{

}

Admittance::Admittance(double Mag, double Theta) :
    admittance(std::polar(Mag, Theta))
{

}

Impedance Admittance::toImpedance()
{
    return Impedance(1.0 / admittance);
}
