#ifndef IMPEDANCE_H
#define IMPEDANCE_H

#include <complex>

typedef std::complex<double> complex;

class Admittance;

class Impedance
{
    friend class Admittance;

public:
    Impedance(complex impedance);
    Impedance(double Abs, double Theta);

    Admittance toAdmittance() const;

    Impedance operator -() const;

    Impedance& operator+=(const Admittance &other);
    Impedance& operator+=(const Impedance &other);
    Impedance& operator-=(const Admittance &other);
    Impedance& operator-=(const Impedance &other);

    Impedance operator+(const Impedance &other) const;
    Impedance operator-(const Impedance &other) const;
    complex operator/(const Impedance &other) const;
    bool operator==(const Impedance &other) const;

private:
    complex impedance;
};

#endif // IMPEDANCE_H
