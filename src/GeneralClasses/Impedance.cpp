#include "include/GeneralClasses/Impedance.h"
#include "include/GeneralClasses/Admittance.h"

Impedance::Impedance(std::complex<double> impedance) :
    impedance(impedance)
{

}

Impedance::Impedance(double Mag, double Theta) :
    impedance(std::polar(Mag, Theta))
{

}

Admittance Impedance::toAdmittance()
{
    return Admittance(1.0 / impedance);
}
