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

Admittance::Admittance(const Admittance &other) :
    admittance(other.admittance)
{

}

Admittance::Admittance(const Impedance &other) :
    admittance(1.0 / other.impedance)
{

}

Impedance Admittance::toImpedance() const
{
    return Impedance(1.0 / admittance);
}

Admittance Admittance::operator -() const
{
    return Admittance(-admittance);
}

Admittance& Admittance::operator +=(const Admittance &other)
{
    admittance += other.admittance;
    return *this;
}

Admittance& Admittance::operator +=(const Impedance &other)
{
    operator +=(other.toAdmittance());
    return *this;
}

Admittance& Admittance::operator -=(const Admittance &other)
{
    admittance -= other.admittance;
    return *this;
}

Admittance& Admittance::operator -=(const Impedance &other)
{
    operator +=(- other.toAdmittance());
    return *this;
}

Admittance Admittance::operator +(const Admittance &other) const
{
    return Admittance(admittance + other.admittance);
}

Admittance Admittance::operator -(const Admittance &other) const
{
    return Admittance(admittance - other.admittance);
}
