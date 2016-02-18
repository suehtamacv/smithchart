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

Admittance Impedance::toAdmittance() const
{
    return Admittance(*this);
}

Impedance Impedance::operator -() const
{
    return Impedance(-impedance);
}

Impedance& Impedance::operator +=(const Impedance &other)
{
    impedance += other.impedance;
    return *this;
}

Impedance& Impedance::operator +=(const Admittance &other)
{
    operator +=(other.toImpedance());
    return *this;
}

Impedance& Impedance::operator -=(const Impedance &other)
{
    impedance -= other.impedance;
    return *this;
}

Impedance& Impedance::operator -=(const Admittance &other)
{
    operator +=(- other.toImpedance());
    return *this;
}

Impedance Impedance::operator +(const Impedance &other) const
{
    return Impedance(impedance + other.impedance);
}

Impedance Impedance::operator -(const Impedance &other) const
{
    return Impedance(impedance - other.impedance);
}
